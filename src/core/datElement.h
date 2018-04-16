//=======================================================================================
// datElement.h
// IFT3100-13
//=======================================================================================
#pragma once

#include "datDependencies.h"
#include "datBoundingBox.h"
#include "datId.h"
#include "datNonCopyableClass.h"
#include "datGeometry.h"

BEGIN_DAT_NAMESPACE

// Forward declarations
struct datElement;
struct datPolyline;
struct datImage;
struct datTextString;
struct datAssimpModel;
struct datLight;
struct datParametricCurve;
struct datMesh;

//=======================================================================================
// Display parameters for geometries
//=======================================================================================
struct datDisplayParams {

public:
    ofColor fillColor;
    ofColor lineColor;
    float lineWidth;
    bool isFilled;

    datDisplayParams():
        fillColor(0,0,0),
        lineColor(0,0,0),
        lineWidth(4.0),
        isFilled(false){
    }
};

//=======================================================================================
// Interface class for elements that support display parameters
//=======================================================================================
struct ISupportDisplayParams
{
protected:
    datDisplayParams m_displayParams;

protected:
    virtual void _OnDisplayParamsSet() {}

public:
    void SetDisplayParams(datDisplayParams const& params) { m_displayParams = params; _OnDisplayParamsSet(); }
    datDisplayParams const& GetDisplayParams() const { return m_displayParams; }
};

//=======================================================================================
// Interface class for elements that support materials
//=======================================================================================
struct ISupportMaterial
{
protected:
    ofMaterial m_material;
    bool m_useMaterial;

protected:
    ISupportMaterial() : m_useMaterial(false) {}
    virtual void _OnMaterialSet() {}

public:
    void SetMaterial(ofMaterial const& material) { m_material = material; }
    ofMaterial const& GetMaterial() const { return m_material; }

    void SetUseMaterial(bool yesNo) { m_useMaterial = yesNo; }
    bool GetUseMaterial() const { return m_useMaterial; }
};


//=======================================================================================
// Base class for 3d scene objects
// Geometries should be kept in local element coordinates
// and transformed in world coordinates through the transformation information in m_node
//=======================================================================================
struct datElement
{
protected:
    datId m_id;     // Id of the element
    ofNode m_node;  // Keeps transformation information (position, orientation, scale)

protected:
    datElement() {}

    virtual std::unique_ptr<datElement> _Clone() const = 0;
    virtual datBoundingBox _CalculateBoundingBox() const = 0;
    virtual void _Draw() const = 0;
    virtual bool _IsHitByRay(datRay const& ray) const = 0;

    virtual ofNode& _GetNode() { return m_node; }
    virtual void _SetNode(ofNode const& node) { m_node = node; }

    virtual ISupportDisplayParams const* _ToSupportDisplayParams() const { return nullptr; }
    virtual ISupportMaterial const* _ToSupportMaterial() const { return nullptr; }

    virtual datPolyline const* _ToPolylineElement() const { return nullptr; }
    virtual datImage const* _ToImageElement() const { return nullptr; }
    virtual datTextString const* _ToTextStringElement() const { return nullptr; }
    virtual datAssimpModel const* _ToAssimpModelElement() const { return nullptr; }
    virtual datLight const* _ToLightElement() const { return nullptr; }
    virtual datParametricCurve const* _ToParametricCurveElement() const { return nullptr; }
    virtual datMesh const* _ToMeshElement() const { return nullptr; }

public:
    virtual ~datElement() {}

    std::unique_ptr<datElement> Clone() const { return _Clone(); }
    datBoundingBox CalculateBoundingBox() const { return _CalculateBoundingBox(); }
    void Draw() const { return _Draw(); }

    // Determines if the ray hits the element
    bool IsHitByRay(datRay const& ray) const { return _IsHitByRay(ray); }

    // only scene should call this
    void AssignId(datId id) { m_id = id; }
    datId GetId() const { return m_id; }

    ofMatrix4x4 GetElementToWorldTransform() const { return const_cast<datElement*>(this)->_GetNode().getGlobalTransformMatrix(); }
    ofNode& GetNode() { return _GetNode(); }
    void SetNode(ofNode const& node) { m_node = node; }


    ISupportDisplayParams const* ToSupportDisplayParams() const { return _ToSupportDisplayParams(); }
    ISupportMaterial const* ToSupportMaterial() const { return _ToSupportMaterial(); }

    datPolyline const* ToPolylineElement() const { return _ToPolylineElement(); }
    datImage const* ToImageElement() const { return _ToImageElement(); }
    datTextString const* ToTextStringElement() const { return _ToTextStringElement(); }
    datAssimpModel const* ToAssimpModelElement() const { return _ToAssimpModelElement(); }
    datLight const* ToLightElement() const { return _ToLightElement(); }
    datParametricCurve const* ToParametricCurveElement() const { return _ToParametricCurveElement(); }
    datMesh const* ToMeshElement() const { return _ToMeshElement(); }
};


//=======================================================================================
// Polyline object
//=======================================================================================
struct datPolyline : datElement, ISupportDisplayParams, ISupportMaterial {
DEFINE_T_SUPER(datElement)

protected:
    ofPolyline m_polyline;

protected:
    datPolyline(std::vector<ofPoint> const& points, bool isClosed);

    virtual std::unique_ptr<datElement> _Clone() const override;
    virtual datBoundingBox _CalculateBoundingBox() const override;
    virtual void _Draw() const override;
    virtual bool _IsHitByRay(datRay const& ray) const override;

    virtual void _OnDisplayParamsSet() override;
    virtual ISupportDisplayParams const* _ToSupportDisplayParams() const override final { return this; }
    virtual ISupportMaterial const* _ToSupportMaterial() const override final { return this; }
    virtual datPolyline const* _ToPolylineElement() const override final { return this; }

public:
    void SetIsClosed(bool yesNo) { m_polyline.setClosed(yesNo); m_displayParams.isFilled = yesNo; }
    void SetPoints(std::vector<ofPoint> const& points) { m_polyline.clear(); m_polyline.addVertices(points); }

    static std::unique_ptr<datPolyline> Create(std::vector<ofPoint> const& points, bool isClosed);
};


//=======================================================================================
// Image object
//=======================================================================================
struct datImage : datElement, ISupportMaterial {

DEFINE_T_SUPER(datElement)

protected:
    ofImage m_image;
    uint32_t m_width;
    uint32_t m_height;

protected:
    datImage(ofImage const& image, uint32_t width, uint32_t height, ofNode const& transform);

    virtual std::unique_ptr<datElement> _Clone() const override;
    virtual datBoundingBox _CalculateBoundingBox() const override;
    virtual void _Draw() const override;
    virtual bool _IsHitByRay(datRay const& ray) const override;
    virtual ISupportMaterial const* _ToSupportMaterial() const override final { return this; }
    virtual datImage const* _ToImageElement() const override final { return this; }

public:
    void SetWidth(uint32_t width) { m_width = width; }
    void SetHeight(uint32_t height) { m_height = height; }
    
    static std::unique_ptr<datImage> Create(ofImage const& image, uint32_t width, uint32_t height, ofNode const& transform);
};


//=======================================================================================
// TextString object
//=======================================================================================
struct datTextString : datElement, ISupportDisplayParams, ISupportMaterial {

DEFINE_T_SUPER(datElement)

protected:
    ofTrueTypeFont m_trueTypeFont;
    std::string m_text;

protected:
    datTextString(ofTrueTypeFont const& ttf, std::string const& text, ofNode const& transform);

    virtual std::unique_ptr<datElement> _Clone() const override;
    virtual datBoundingBox _CalculateBoundingBox() const override;
    virtual void _Draw() const override;
    virtual bool _IsHitByRay(datRay const& ray) const override;
    virtual ISupportDisplayParams const* _ToSupportDisplayParams() const override final { return this; }
    virtual ISupportMaterial const* _ToSupportMaterial() const override final { return this; }
    virtual datTextString const* _ToTextStringElement() const override final { return this; }

public:
    void SetText(std::string const& text) { m_text = text; }

    static std::unique_ptr<datTextString> Create(ofTrueTypeFont const& ttf, std::string const& text, ofNode const& transform);
};


//=======================================================================================
// Models from ofxAssimpModelLoader
//=======================================================================================
struct datAssimpModel : datElement {

DEFINE_T_SUPER(datElement)

protected:
    ofxAssimpModelLoader m_model;

protected:
    datAssimpModel(ofxAssimpModelLoader const& model, ofNode const& transform);

    virtual std::unique_ptr<datElement> _Clone() const override;
    virtual datBoundingBox _CalculateBoundingBox() const override;
    virtual void _Draw() const override;
    virtual bool _IsHitByRay(datRay const& ray) const override;
    virtual datAssimpModel const* _ToAssimpModelElement() const override final { return this; }

public:
    static std::unique_ptr<datAssimpModel> Create(ofxAssimpModelLoader const& model, ofNode const& transform);
};


//=======================================================================================
// Light object
//=======================================================================================
struct datLight : datElement {

DEFINE_T_SUPER(datElement)

protected:
    ofLight m_light;

protected:
    datLight(ofLight const& light);

    virtual std::unique_ptr<datElement> _Clone() const override;
    virtual datBoundingBox _CalculateBoundingBox() const override;
    virtual void _Draw() const override;
    virtual bool _IsHitByRay(datRay const& ray) const override;
    virtual ofNode& _GetNode() override { return m_light; }
    virtual void _SetNode(ofNode const& node) override { static_cast<ofNode&>(m_light) = node; }
    virtual datLight const* _ToLightElement() const override final { return this; }

public:
    ofLight& GetOfLightR() { return m_light; }
    void SetEnabled(bool yesNo) { yesNo ? m_light.enable() : m_light.disable(); }

    static std::unique_ptr<datLight> Create(ofLight const& light);
};


//=======================================================================================
// Parametric curve
//=======================================================================================
struct datParametricCurve : datElement, ISupportDisplayParams {

DEFINE_T_SUPER(datElement)

public:
    enum class Type { Invalid, Bezier, Hermite, BSpline, CatmullRom};

protected:
    Type m_type;
    std::vector<ofPoint> m_controlPoints;
    ofPolyline m_polyline; // Approximation of the parametric curve

protected:
    datParametricCurve(Type type);

    virtual std::unique_ptr<datElement> _Clone() const override;
    virtual datBoundingBox _CalculateBoundingBox() const override;
    virtual void _Draw() const override;
    virtual bool _IsHitByRay(datRay const& ray) const override;
    virtual ISupportDisplayParams const* _ToSupportDisplayParams() const override final { return this; }
    virtual datParametricCurve const* _ToParametricCurveElement() const override final { return this; }

    void AssignPointsAndEvaluate(std::vector<ofPoint> const& controlPoints);
    ofPoint Evaluate(ofPoint const* pPoints, float t) const;
    ofPoint EvaluateBezier(ofPoint const* pPoints, float t) const;
    ofPoint EvaluateHermite(ofPoint const* pPoints, float t) const;
    ofPoint EvaluateBSpline(ofPoint const* pPoints, float t) const;
    ofPoint EvaluateCatmullRom(ofPoint const* pPoints, float t) const;

public:
    static std::unique_ptr<datParametricCurve> CreateBezier(std::vector<ofPoint> controlPoints);
    static std::unique_ptr<datParametricCurve> CreateHermite(ofPoint const& p1, ofPoint const& p2, ofVec3f const& v1, ofVec3f const& v2);
    static std::unique_ptr<datParametricCurve> CreateBSpline(std::vector<ofPoint> const& controlPoints);
    static std::unique_ptr<datParametricCurve> CreateCatmullRom(std::vector<ofPoint> const& controlPoints);
};


//=======================================================================================
// Mesh scene object
//=======================================================================================
struct datMesh : datElement, ISupportDisplayParams, ISupportMaterial {
    DEFINE_T_SUPER(datElement)

protected:
    ofMesh m_mesh;

protected:
    datMesh(ofMesh const& mesh);

    virtual std::unique_ptr<datElement> _Clone() const override;
    virtual datBoundingBox _CalculateBoundingBox() const override;
    virtual void _Draw() const override;
    virtual bool _IsHitByRay(datRay const& ray) const override;

    virtual ISupportDisplayParams const* _ToSupportDisplayParams() const override final { return this; }
    virtual ISupportMaterial const* _ToSupportMaterial() const override final { return this; }
    virtual datMesh const* _ToMeshElement() const override final { return this; }

public:
    void SetMesh(ofMesh const& mesh) { m_mesh = mesh; }

    static std::unique_ptr<datMesh> Create(ofMesh const& mesh);
};



END_DAT_NAMESPACE
