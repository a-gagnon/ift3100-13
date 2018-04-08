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


namespace {

    static datEditAttributesTool* s_tool = nullptr;

    void setNoMaterial() { s_tool->applyMaterial(0); }
    void setMaterial1() { s_tool->applyMaterial(1); }
    void setMaterial2() { s_tool->applyMaterial(2); }
    void setMaterial3() { s_tool->applyMaterial(3); }
    ofEvent<ofxButton> setMaterialEvent;
};


datEditAttributesTool::datEditAttributesTool():
    m_radioNoMaterial(setNoMaterial, setMaterialEvent),
    m_radioMaterial1(setMaterial1, setMaterialEvent),
    m_radioMaterial2(setMaterial2, setMaterialEvent),
    m_radioMaterial3(setMaterial3, setMaterialEvent) {
    s_tool = this;
}


datEditAttributesTool::~datEditAttributesTool() {
    s_tool = nullptr;
}


void datEditAttributesTool::onStartTool() {

    datScene& scene = GetRenderer().GetScene();
    std::set<datId> selectedIds = scene.GetSelection();

    // Take a cloned copy of selected elements, and a copy of the current transform
    for (auto const& id : selectedIds) {
        m_elements.push_back(scene.GetElement(id)->Clone());
        m_originalTransforms.push_back(m_elements.back()->GetNode());
        GetRenderer().AddTransient(m_elements.back().get());
    }

    GetRenderer().SetNeverDraw(selectedIds);

    assert(!m_elements.empty());

    bool hasStyleGroup = false;
    bool hasMaterialGroup = false;

    for (auto const& element : m_elements) {
        if (nullptr != element->ToSupportDisplayParams())
            hasStyleGroup = true;

        if (nullptr != element->ToSupportMaterial())
            hasMaterialGroup = true;
    }

    m_panel.setup("Tool settings", "", 0.4 * ofGetWidth());
    m_panel.add(m_geometryGroup.setup(datLocalization::GeometryParams()));
    m_geometryGroup.add(m_paramScale.set(datLocalization::GeometryParams_Scale(), 1.0, SCALE_MIN, SCALE_MAX));
    m_geometryGroup.add(m_paramRotate.set(datLocalization::GeometryParams_Rotate(), 0.0, ROTATE_MIN, ROTATE_MAX));
    m_geometryGroup.add(m_paramTranslate.set(datLocalization::GeometryParams_Translate(),
        ofVec3f(0, 0), ofVec3f(TRANSLATE_MIN, TRANSLATE_MIN, TRANSLATE_MIN), ofVec3f(TRANSLATE_MAX, TRANSLATE_MAX, TRANSLATE_MAX)));

    if (hasStyleGroup) {
        m_panel.add(m_styleGroup.setup(datLocalization::DisplayParams()));
        m_styleGroup.add(m_paramLineColor.set(datLocalization::DisplayParams_LineColor(), GetRenderer().GetActiveDisplayParams().lineColor, ofColor(0, 0, 0), ofColor(255, 255, 255)));
        m_styleGroup.add(m_paramLineWidth.set(datLocalization::DisplayParams_LineWidth(), GetRenderer().GetActiveDisplayParams().lineWidth, LINEWIDTH_MIN, LINEWIDTH_MAX));
        m_styleGroup.add(m_paramFillColor.set(datLocalization::DisplayParams_FillColor(), GetRenderer().GetActiveDisplayParams().fillColor, ofColor(0, 0, 0), ofColor(255, 255, 255)));
    }

    if (hasMaterialGroup) {
        m_panel.add(m_materialGroup.setup(datLocalization::Materials()));
        m_materialGroup.add(m_radioNoMaterial.setup(datLocalization::NoMaterial()));
        m_materialGroup.add(m_radioMaterial1.setup(datLocalization::Material1()));
        m_materialGroup.add(m_radioMaterial2.setup(datLocalization::Material2()));
        m_materialGroup.add(m_radioMaterial3.setup(datLocalization::Material3()));
    }

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
    GetRenderer().GetScene().UpdateElements(std::move(m_elements));
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

    for (auto const& element : m_elements) {
        if (auto pSupport = dynamic_cast<ISupportDisplayParams*>(element.get())) {
            datDisplayParams params = pSupport->GetDisplayParams();
            params.lineColor = color;
            pSupport->SetDisplayParams(params);
        }
    }
}


void datEditAttributesTool::onLineWidthChanged(float& value) {

    for (auto const& element : m_elements) {
        if (auto pSupport = dynamic_cast<ISupportDisplayParams*>(element.get())) {
            datDisplayParams params = pSupport->GetDisplayParams();
            params.lineWidth = value;
            pSupport->SetDisplayParams(params);
        }
    }
}


void datEditAttributesTool::onFillColorChanged(ofColor& color) {

    for (auto const& element : m_elements) {
        if (auto pSupport = dynamic_cast<ISupportDisplayParams*>(element.get())) {
            datDisplayParams params = pSupport->GetDisplayParams();
            params.fillColor = color;
            pSupport->SetDisplayParams(params);
        }
    }
}


void datEditAttributesTool::onScaleChanged(float& value) {
    applyTransforms();
}

void datEditAttributesTool::onRotationChanged(float& value) {
    applyTransforms();
}

void datEditAttributesTool::onTranslationChanged(ofVec3f& value) {
    applyTransforms();
}


void datEditAttributesTool::applyTransforms() {

    for (size_t i = 0; i < m_elements.size(); ++i) {

        ofNode node = m_originalTransforms[i];
        node.setScale(m_paramScale * node.getScale());
        node.rotate(m_paramRotate, 0.0, 0.0, 1.0);
        node.move(m_paramTranslate);

        m_elements[i]->SetNode(node);
    }
}


void datEditAttributesTool::applyMaterial(int value) {

    for (auto const& element : m_elements) {
        if (auto pSupport = dynamic_cast<ISupportMaterial*>(element.get())) {

            if (0 == value) {
                pSupport->SetUseMaterial(false);
            }
            else if (1 == value) {
                pSupport->SetUseMaterial(true);
                pSupport->SetMaterial(GetRenderer().GetMaterial1());
            }
            else if (2 == value) {
                pSupport->SetUseMaterial(true);
                pSupport->SetMaterial(GetRenderer().GetMaterial2());
            }
            else if (3 == value) {
                pSupport->SetUseMaterial(true);
                pSupport->SetMaterial(GetRenderer().GetMaterial3());
            }
        }
    }
}


void datEditAttributesTool::onDraw() {
    m_panel.draw();
}
