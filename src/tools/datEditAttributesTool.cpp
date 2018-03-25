//=======================================================================================
// datEditAttributesTool.cpp
// IFT3100-13
//=======================================================================================
#include "datEditAttributesTool.h"

USING_DAT_NAMESPACE

#define LINEWIDTH_MIN 0.01f
#define LINEWIDTH_MAX 12.0f
#define ROTATE_MIN -180
#define ROTATE_MAX 180
#define SCALE_MIN 0.5
#define SCALE_MAX 2.0
#define TRANSLATE_MIN -500
#define TRANSLATE_MAX 500

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
        GetRenderer().AddTransient(m_geometries.back().get());
    }

    GetRenderer().SetNeverDraw(selectedIds);

    assert(!m_geometries.empty());

    m_panel.setup("Tool settings", "", 0.4 * ofGetWidth());
    m_panel.add(m_styleGroup.setup(datLocalization::DisplayParams()));
    m_styleGroup.add(m_paramLineColor.set(datLocalization::DisplayParams_LineColor(), GetRenderer().GetActiveDisplayParams().lineColor, ofColor(0, 0, 0), ofColor(255, 255, 255)));
    m_styleGroup.add(m_paramLineWidth.set(datLocalization::DisplayParams_LineWidth(), GetRenderer().GetActiveDisplayParams().lineWidth, LINEWIDTH_MIN, LINEWIDTH_MAX));
    m_styleGroup.add(m_paramFillColor.set(datLocalization::DisplayParams_FillColor(), GetRenderer().GetActiveDisplayParams().fillColor, ofColor(0, 0, 0), ofColor(255, 255, 255)));

    m_panel.add(m_geometryGroup.setup(datLocalization::GeometryParams()));
    m_geometryGroup.add(m_paramScale.set(datLocalization::GeometryParams_Scale(), 1.0, SCALE_MIN, SCALE_MAX));
    m_geometryGroup.add(m_paramRotate.set(datLocalization::GeometryParams_Rotate(), 0.0, ROTATE_MIN, ROTATE_MAX));
    m_geometryGroup.add(m_paramTranslate.set(datLocalization::GeometryParams_Translate(), ofVec2f(0, 0), ofVec2f(TRANSLATE_MIN, TRANSLATE_MIN), ofVec2f(TRANSLATE_MAX, TRANSLATE_MAX)));
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
    GetRenderer().ClearTransients();

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
}
