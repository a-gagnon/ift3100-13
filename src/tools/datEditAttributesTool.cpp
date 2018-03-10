//=======================================================================================
// datEditAttributesTool.cpp
// IFT3100-13
//=======================================================================================
#include "datEditAttributesTool.h"

USING_DAT_NAMESPACE

datEditAttributesTool::datEditAttributesTool() {
}


datEditAttributesTool::~datEditAttributesTool() {
}


void datEditAttributesTool::onStartTool() {

    datScene& scene = GetRenderer().GetScene();
    std::set<datId> selectedIds = scene.GetSelection();

    // Take a cloned copy of selected elements, and a copy of the current transform
    for (auto const& id : selectedIds) {
        m_geometries.push_back(scene.GetGeometry(id)->Clone());
        m_originalTransforms.push_back(m_geometries.back()->GetTransform());
    }

    GetRenderer().SetNeverDraw(selectedIds);

    assert(!m_geometries.empty());

    m_panel.setup("Tool settings", "", 0.4 * ofGetWidth());
    m_panel.add(m_styleGroup.setup(datLocalization::DisplayParams()));
    m_styleGroup.add(m_paramLineColor.set(datLocalization::DisplayParams_LineColor(), GetRenderer().GetActiveDisplayParams().lineColor, ofColor(0, 0, 0), ofColor(255, 255, 255)));
    m_styleGroup.add(m_paramLineWidth.set(datLocalization::DisplayParams_LineWidth(), GetRenderer().GetActiveDisplayParams().lineWidth, 0.01f, 12.0f));
    m_styleGroup.add(m_paramFillColor.set(datLocalization::DisplayParams_FillColor(), GetRenderer().GetActiveDisplayParams().fillColor, ofColor(0, 0, 0), ofColor(255, 255, 255)));

    m_panel.add(m_geometryGroup.setup(datLocalization::GeometryParams()));
    m_geometryGroup.add(m_paramScale.set(datLocalization::GeometryParams_Scale(), 1.0, 0.5, 2.0));
    m_geometryGroup.add(m_paramRotate.set(datLocalization::GeometryParams_Rotate(), 0.0, -180, 180));
    m_geometryGroup.add(m_paramTranslate.set(datLocalization::GeometryParams_Translate(), ofVec2f(0, 0), ofVec2f(-500, -500), ofVec2f(500, 500)));
    m_panel.setPosition(ofGetWidth() - m_panel.getWidth() - 10.0, 10.0);

    m_paramLineColor.addListener(this, &datEditAttributesTool::onLineColorChanged);
    m_paramLineWidth.addListener(this, &datEditAttributesTool::onLineWidthChanged);
    m_paramFillColor.addListener(this, &datEditAttributesTool::onFillColorChanged);
    m_paramScale.addListener(this, &datEditAttributesTool::onScaleChanged);
    m_paramRotate.addListener(this, &datEditAttributesTool::onRotationChanged);
    m_paramTranslate.addListener(this, &datEditAttributesTool::onTranslationChanged);
}


void datEditAttributesTool::onExitTool() {

    // Commit changes to elements
    GetRenderer().GetScene().UpdateMultipleGeometries(std::move(m_geometries));
    GetRenderer().ClearNeverDraw();

    m_paramLineColor.removeListener(this, &datEditAttributesTool::onLineColorChanged);
    m_paramLineWidth.removeListener(this, &datEditAttributesTool::onLineWidthChanged);
    m_paramFillColor.removeListener(this, &datEditAttributesTool::onFillColorChanged);
    m_paramScale.removeListener(this, &datEditAttributesTool::onScaleChanged);
    m_paramRotate.removeListener(this, &datEditAttributesTool::onRotationChanged);
    m_paramTranslate.removeListener(this, &datEditAttributesTool::onTranslationChanged);
}


void datEditAttributesTool::onLineColorChanged(ofColor& color) {
    for (auto const& geometry : m_geometries) {
        geometry->GetDisplayParamsR().lineColor = color;
    }
}


void datEditAttributesTool::onLineWidthChanged(float& value) {
    for (auto const& geometry : m_geometries) {
        geometry->GetDisplayParamsR().lineWidth = value;
    }
}


void datEditAttributesTool::onFillColorChanged(ofColor& color) {
    for (auto const& geometry : m_geometries) {
        geometry->GetDisplayParamsR().fillColor = color;
    }
}


void datEditAttributesTool::onScaleChanged(float& value) {
    applyTransforms();
}

void datEditAttributesTool::onRotationChanged(float& value) {
    applyTransforms();
}

void datEditAttributesTool::onTranslationChanged(ofVec2f& value) {
    applyTransforms();
}


void datEditAttributesTool::applyTransforms() {

    for (size_t i = 0; i < m_geometries.size(); ++i) {

        datTransform transform = m_originalTransforms[i];
        transform.scale(m_paramScale, m_paramScale, m_paramScale);
        transform.rotate(m_paramRotate, 0, 0, 1.0);

        ofPoint translation = transform.getTranslation();
        translation.x += m_paramTranslate.get().x;
        translation.y += m_paramTranslate.get().y;
        transform.setTranslation(translation);

        datGeometry* pGeometry = m_geometries[i].get();
        pGeometry->SetTransform(transform);
    }

}


void datEditAttributesTool::onDraw() {
    m_panel.draw();
    datRenderer& renderer = GetRenderer();

    ofEnableDepthTest();

    for (auto const& geometry : m_geometries) {
        renderer.DrawGeometry(*geometry, true);
    }

    ofDisableDepthTest();
}
