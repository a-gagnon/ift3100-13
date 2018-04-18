//=======================================================================================
// datElement.cpp
// IFT3100-13
//=======================================================================================
#include "datElement.h"

USING_DAT_NAMESPACE


//---------------------------------------------------------------------------------------
// datPolyline
//---------------------------------------------------------------------------------------
datPolyline::datPolyline(std::vector<ofPoint> const& points, bool isClosed) :
    T_Super() {
    SetPoints(points);
    SetIsClosed(isClosed);
}


std::unique_ptr<datPolyline> datPolyline::Create(std::vector<ofPoint> const& points, bool isClosed) {
    auto ptr = std::unique_ptr<datPolyline>(new datPolyline(points, isClosed));
    return std::move(ptr);
}


std::unique_ptr<datElement> datPolyline::_Clone() const {
    auto ptr = std::unique_ptr<datElement>(new datPolyline(*this));
    return std::move(ptr);
}


datBoundingBox datPolyline::_CalculateBoundingBox() const {

    std::vector<ofPoint> const& localPoints = m_polyline.getVertices();
    const ofMatrix4x4 transform = GetElementToWorldTransform();
    return datBoundingBox::FromPoints(localPoints, &transform);
}


void datPolyline::_Draw() const {

    ofPushMatrix();
    ofMatrix4x4 elementToWorld = GetElementToWorldTransform();
    ofMultMatrix(elementToWorld);

    if (!m_polyline.isClosed()) {
        m_polyline.draw();
    }
    else {
        // For some reason, calling draw on ofPolyline doesn't apply fill properly
        std::vector<ofPoint> const& points = m_polyline.getVertices();

        ofBeginShape();
        for (auto const& point : points) {
            ofVertex(point.x, point.y, point.z);
        }
        ofEndShape();
    }

    ofPopMatrix();
}



bool datPolyline::_IsHitByRay(datRay const& ray) const {

    static float s_threshold = 0.5;

    const ofMatrix4x4 transform = GetElementToWorldTransform();
    std::vector<ofPoint> vertices = m_polyline.getVertices();

    for (auto& vertex : vertices) {
        vertex = vertex * transform;
    }

    for (size_t i = 1; i < vertices.size(); ++i) {

        ofVec3f direction = vertices[i] - vertices[i - 1];
        datRay lineRay(vertices[i - 1], direction);

        float distance = ray.DistanceLineLine(lineRay);
        if (s_threshold > distance)
            return true;
    }

    return false;
}


void datPolyline::_OnDisplayParamsSet() {
    // Make sure display params are consistent with the geometry structure
    m_polyline.setClosed(m_displayParams.isFilled);
}



//---------------------------------------------------------------------------------------
// datImage
//---------------------------------------------------------------------------------------
datImage::datImage(ofImage const& image, uint32_t width, uint32_t height, ofNode const& transform) :
    T_Super(),
    m_image(image),
    m_width(width),
    m_height(height) {

    assert(m_image.isAllocated());
    m_node = transform;
}


std::unique_ptr<datImage> datImage::Create(ofImage const& image, uint32_t width, uint32_t height, ofNode const& transform) {
    auto ptr = std::unique_ptr<datImage>(new datImage(image, width, height, transform));
    return std::move(ptr);
}


std::unique_ptr<datElement> datImage::_Clone() const {
    auto ptr = std::unique_ptr<datElement>(new datImage(*this));
    return std::move(ptr);
}


datBoundingBox datImage::_CalculateBoundingBox() const {

    std::vector<ofPoint> corners;
    corners.push_back(ofPoint(0, 0, 0));
    corners.push_back(ofPoint(m_width, 0, 0));
    corners.push_back(ofPoint(m_width, m_height, 0));
    corners.push_back(ofPoint(0, m_height, 0));

    ofMatrix4x4 transform = GetElementToWorldTransform();
    return datBoundingBox::FromPoints(corners, &transform);
}


void datImage::_Draw() const {

    ofPushStyle();
    ofSetColor(255);

    ofPushMatrix();
    ofMatrix4x4 elementToWorld = GetElementToWorldTransform();
    ofMultMatrix(elementToWorld);

    m_image.draw(0, 0, m_width, m_height);

    ofPopMatrix();
    ofPopStyle();
}


bool datImage::_IsHitByRay(datRay const& ray) const {

    ofPoint origin = m_node.getGlobalPosition();
    ofPoint normal = m_node.getZAxis();
    datPlane plane(origin, normal);

    ofPoint intersectionPoint;
    if (!ray.IntersectPlane(plane, &intersectionPoint))
        return false;

    // make the intersection point relative to the plane origin
    ofPoint relPoint = intersectionPoint - origin;

    float xDist = m_node.getXAxis().dot(relPoint);
    if (xDist < 0 || xDist > m_width)
        return false;

    float yDist = m_node.getYAxis().dot(relPoint);
    if (yDist < 0 || yDist > m_height)
        return false;

    return true;
}


//---------------------------------------------------------------------------------------
// datTextString
//---------------------------------------------------------------------------------------
datTextString::datTextString(ofTrueTypeFont const& ttf, std::string const& text, ofNode const& transform) :
    T_Super(),
    m_trueTypeFont(ttf),
    m_text(text) {

    assert(m_trueTypeFont.isLoaded());
    m_node = transform;
}


std::unique_ptr<datTextString> datTextString::Create(ofTrueTypeFont const& ttf, std::string const& text, ofNode const& transform) {
    auto ptr = std::unique_ptr<datTextString>(new datTextString(ttf, text, transform));
    return std::move(ptr);
}


std::unique_ptr<datElement> datTextString::_Clone() const {
    auto ptr = std::unique_ptr<datTextString>(new datTextString(*this));
    return std::move(ptr);
}


datBoundingBox datTextString::_CalculateBoundingBox() const {

    const ofRectangle rect = m_trueTypeFont.getStringBoundingBox(m_text, 0, 0);

    std::vector<ofPoint> corners;
    corners.push_back(rect.getTopLeft());
    corners.push_back(rect.getBottomLeft());
    corners.push_back(rect.getBottomRight());
    corners.push_back(rect.getTopRight());

    ofMatrix4x4 transform = GetElementToWorldTransform();
    return datBoundingBox::FromPoints(corners, &transform);
}


void datTextString::_Draw() const {

    ofPushMatrix();
    ofMatrix4x4 elementToWorld = GetElementToWorldTransform();
    ofMultMatrix(elementToWorld);

    m_trueTypeFont.drawString(m_text, 0, 0);

    ofPopMatrix();
}


bool datTextString::_IsHitByRay(datRay const& ray) const {

    datBoundingBox aabb = CalculateBoundingBox();
    return ray.IntersectBox(aabb);
}



//---------------------------------------------------------------------------------------
// datAssimpModel
//---------------------------------------------------------------------------------------
datAssimpModel::datAssimpModel(ofxAssimpModelLoader const& model, ofNode const& transform) :
    T_Super(),
    m_model(model) {

    m_node = transform;
}


std::unique_ptr<datAssimpModel> datAssimpModel::Create(ofxAssimpModelLoader const& model, ofNode const& transform) {
    auto ptr = std::unique_ptr<datAssimpModel>(new datAssimpModel(model, transform));
    return std::move(ptr);
}


std::unique_ptr<datElement> datAssimpModel::_Clone() const {
    auto ptr = std::unique_ptr<datAssimpModel>(new datAssimpModel(*this));
    return std::move(ptr);
}


datBoundingBox datAssimpModel::_CalculateBoundingBox() const {

    // const-correctness of ofxAssimpModelLoader is awful...
    datAssimpModel& thisR = const_cast<datAssimpModel&>(*this);

    std::vector<ofPoint> corners;
    corners.push_back(thisR.m_model.getSceneMin(true));
    corners.push_back(thisR.m_model.getSceneMax(true));

    for (auto& corner : corners) {
        corner *= thisR.m_model.getNormalizedScale();
        corner += thisR.m_model.getPosition();
    }

    ofMatrix4x4 transform = GetElementToWorldTransform();
    return datBoundingBox::FromPoints(corners, &transform);
}


void datAssimpModel::_Draw() const {

    ofPushMatrix();
    ofMatrix4x4 elementToWorld = GetElementToWorldTransform();
    ofMultMatrix(elementToWorld);

    datAssimpModel& thisR = const_cast<datAssimpModel&>(*this);
    thisR.m_model.drawFaces();

    ofPopMatrix();
}


bool datAssimpModel::_IsHitByRay(datRay const& ray) const {

    datBoundingBox aabb = CalculateBoundingBox();
    return ray.IntersectBox(aabb);
}



//---------------------------------------------------------------------------------------
// datLight
//---------------------------------------------------------------------------------------
datLight::datLight(ofLight const& light):
    T_Super(),
    m_light(light) {
}


std::unique_ptr<datLight> datLight::Create(ofLight const& light) {
    auto ptr = std::unique_ptr<datLight>(new datLight(light));
    return std::move(ptr);
}


std::unique_ptr<datElement> datLight::_Clone() const {
    auto ptr = std::unique_ptr<datElement>(new datLight(*this));
    return std::move(ptr);
}


datBoundingBox datLight::_CalculateBoundingBox() const {

    std::vector<ofPoint> points { ofPoint(0, 0, 0) };
    ofMatrix4x4 transform = GetElementToWorldTransform();

    datBoundingBox box = datBoundingBox::FromPoints(points, &transform);
    box.Expand(2.0);
    return box;
}


void datLight::_Draw() const {
    m_light.draw();
}


bool datLight::_IsHitByRay(datRay const& ray) const {

    datBoundingBox aabb = CalculateBoundingBox();
    return ray.IntersectBox(aabb);
}



//---------------------------------------------------------------------------------------
// datParametricCurve
//---------------------------------------------------------------------------------------
datParametricCurve::datParametricCurve(Type type) :
    T_Super(),
    m_type(type) {
}


std::unique_ptr<datParametricCurve> datParametricCurve::CreateBezier(std::vector<ofPoint> controlPoints) {

    if (4 > controlPoints.size())
        return nullptr;

    controlPoints.resize(4);

    auto ptr = std::unique_ptr<datParametricCurve>(new datParametricCurve(Type::Bezier));
    ptr->AssignPointsAndEvaluate(controlPoints);
    return std::move(ptr);
}


std::unique_ptr<datParametricCurve> datParametricCurve::CreateHermite(ofPoint const& p1, ofPoint const& p2, ofVec3f const& v1, ofVec3f const& v2) {

    std::vector<ofPoint> cPoints;
    cPoints.push_back(p1);
    cPoints.push_back(p2);
    cPoints.push_back(v1);
    cPoints.push_back(v2);

    auto ptr = std::unique_ptr<datParametricCurve>(new datParametricCurve(Type::Hermite));
    ptr->AssignPointsAndEvaluate(cPoints);
    return std::move(ptr);
}


std::unique_ptr<datParametricCurve> datParametricCurve::CreateBSpline(std::vector<ofPoint> const& controlPoints) {

    if (4 > controlPoints.size())
        return nullptr;

    auto ptr = std::unique_ptr<datParametricCurve>(new datParametricCurve(Type::BSpline));
    ptr->AssignPointsAndEvaluate(controlPoints);
    return std::move(ptr);
}


std::unique_ptr<datParametricCurve> datParametricCurve::CreateCatmullRom(std::vector<ofPoint> const& controlPoints) {

    if (4 > controlPoints.size())
        return nullptr;

    auto ptr = std::unique_ptr<datParametricCurve>(new datParametricCurve(Type::CatmullRom));
    ptr->AssignPointsAndEvaluate(controlPoints);
    return std::move(ptr);
}


std::unique_ptr<datElement> datParametricCurve::_Clone() const {
    auto ptr = std::unique_ptr<datElement>(new datParametricCurve(*this));
    return std::move(ptr);
}


datBoundingBox datParametricCurve::_CalculateBoundingBox() const {

    std::vector<ofPoint> const& points = m_polyline.getVertices();
    ofMatrix4x4 transform = GetElementToWorldTransform();

    return datBoundingBox::FromPoints(points, &transform);
}


void datParametricCurve::_Draw() const {

    static float s_sphereRadius = 0.5;

    // Draw control points
    for (auto& cPoint : m_controlPoints) {
        ofDrawSphere(cPoint, s_sphereRadius);
    }

    m_polyline.draw();
}


bool datParametricCurve::_IsHitByRay(datRay const& ray) const {

    static float s_threshold = 0.5;

    const ofMatrix4x4 transform = GetElementToWorldTransform();
    std::vector<ofPoint> vertices = m_polyline.getVertices();

    for (auto& vertex : vertices) {
        vertex = vertex * transform;
    }

    for (size_t i = 1; i < vertices.size(); ++i) {

        ofVec3f direction = vertices[i] - vertices[i - 1];
        datRay lineRay(vertices[i - 1], direction);

        float distance = ray.DistanceLineLine(lineRay);
        if (s_threshold > distance)
            return true;
    }

    return false;
}


void datParametricCurve::AssignPointsAndEvaluate(std::vector<ofPoint> const& controlPoints) {

    assert(4 <= controlPoints.size());

    m_controlPoints = controlPoints;
    m_polyline.clear();

    static size_t s_nSamples = 100;

    size_t nSets = (controlPoints.size() - 1) / 3;
    size_t samplesPerSet = s_nSamples / nSets;
    float step = 1.0 / (samplesPerSet - 1);

    for (size_t i = 0; i < nSets; ++i) {

        for (size_t j = 0; j < samplesPerSet; ++j) {
            ofPoint point = Evaluate(&controlPoints[3 * i], j * step);
            m_polyline.addVertex(point);
        }
    }
}

ofPoint datParametricCurve::Evaluate(ofPoint const* pPoints, float t) const {

    switch (m_type) {
    case Type::Bezier:
        return EvaluateBezier(pPoints, t);
    case Type::Hermite:
        return EvaluateHermite(pPoints, t);
    case Type::BSpline:
        return EvaluateBSpline(pPoints, t);
    case Type::CatmullRom:
        return EvaluateCatmullRom(pPoints, t);
    }

    assert(false); // Invalid curve type
    return ofPoint();
}


ofPoint datParametricCurve::EvaluateBezier(ofPoint const* pPoints, float t) const {

    ofPoint const& p1 = pPoints[0];
    ofPoint const& p2 = pPoints[1];
    ofPoint const& p3 = pPoints[2];
    ofPoint const& p4 = pPoints[3];

    const float a = (1.0 - t);

    // (1 - t)³P1 + 3t(1-t)²P2 + 3t²(1-t)P3 + t³P4
    ofPoint result1 = a * a * a * p1;
    ofPoint result2 = 3 * t * a * a * p2;
    ofPoint result3 = 3 * t * t * a * p3;
    ofPoint result4 = t * t * t * p4;

    ofPoint result = result1 + result2 + result3 + result4;
    return result;
}


bool datParametricCurve::EvaluateBezier(ofPoint& result, float t) const {

    if (Type::Bezier != m_type)
        return false;

    result = EvaluateBezier(m_controlPoints.data(), t);
    return true;
}


ofPoint datParametricCurve::EvaluateHermite(ofPoint const* pPoints, float t) const {

    ofPoint const& p1 = pPoints[0];
    ofPoint const& p2 = pPoints[1];
    ofPoint const& v1 = pPoints[2];
    ofPoint const& v2 = pPoints[3];

    const float aa = (1.0 - t) * (1.0 - t);
    const float t2 = t * t;

    // (1 + 2t)(1 - t)²P1 + t(1 - t)²V1 + t²(t - 1)V2 + t²(3 - 2t)P2
    ofPoint result1 = (1 + 2 * t)*aa*p1;
    ofPoint result2 = t*aa*v1;
    ofPoint result3 = t2*(t - 1.0)*v2;
    ofPoint result4 = t2*(3 - 2 * t)*p2;

    ofPoint result = result1 + result2 + result3 + result4;
    return result;
}


ofPoint datParametricCurve::EvaluateBSpline(ofPoint const* pPoints, float t) const {
    return EvaluateBezier(pPoints, t);
}


ofPoint datParametricCurve::EvaluateCatmullRom(ofPoint const* pPoints, float t) const {

    ofPoint const& p1 = pPoints[0];
    ofPoint const& p2 = pPoints[1];
    ofPoint const& p3 = pPoints[2];
    ofPoint const& p4 = pPoints[3];

    // q(t) = 0.5 *((2 * P2) + (-P1 + P3) * t + (2 * P1 - 5 * P2 + 4 * P3 - P4) * t2 + (-P1 + 3 * P2 - 3 * P3 + P4) * t3)
    ofPoint result1 = 2 * p2;
    ofPoint result2 = (-1 * p1 + p3) * t;
    ofPoint result3 = (2 * p1 - 5 * p2 + 4 * p3 - p4) * t * t;
    ofPoint result4 = (-1 * p1 + 3 * p2 - 3 * p3 + p4) * t * t * t;

    ofPoint result = 0.5 * (result1 + result2 + result3 + result4);
    return result;
}



//---------------------------------------------------------------------------------------
// datMesh
//---------------------------------------------------------------------------------------
datMesh::datMesh(ofMesh const& mesh) :
    T_Super(),
    m_mesh(mesh) {
}


std::unique_ptr<datMesh> datMesh::Create(ofMesh const& mesh) {
    auto ptr = std::unique_ptr<datMesh>(new datMesh(mesh));
    return std::move(ptr);
}


std::unique_ptr<datElement> datMesh::_Clone() const {
    auto ptr = std::unique_ptr<datElement>(new datMesh(*this));
    return std::move(ptr);
}


datBoundingBox datMesh::_CalculateBoundingBox() const {

    std::vector<ofPoint> const& localPoints = m_mesh.getVertices();
    const ofMatrix4x4 transform = GetElementToWorldTransform();
    return datBoundingBox::FromPoints(localPoints, &transform);
}


void datMesh::_Draw() const {

    ofPushMatrix();
    ofMatrix4x4 elementToWorld = GetElementToWorldTransform();
    ofMultMatrix(elementToWorld);

    if (m_displayParams.isFilled)
        m_mesh.drawFaces();
    else
        m_mesh.drawWireframe();

    ofPopMatrix();
}


bool datMesh::_IsHitByRay(datRay const& ray) const {

    //&&AG might be worth doing per-triangle intersection.
    // bounding box for now
    datBoundingBox aabb = CalculateBoundingBox();
    return ray.IntersectBox(aabb);
}

