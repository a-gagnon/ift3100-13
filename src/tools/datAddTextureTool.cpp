//=======================================================================================
// datAddTextureTool.cpp
// IFT3100-13
//=======================================================================================
#include "datAddTextureTool.h"

USING_DAT_NAMESPACE

datAddTextureTool::datAddTextureTool() {
}


datAddTextureTool::~datAddTextureTool() {
}


void datAddTextureTool::onStartTool() {
    
    datScene& scene = GetRenderer().GetScene();
    std::set<datId> selectedIds = scene.GetSelection();

    m_fbo.begin();
    ofClear(0, 0, 0, 0); //Clear the FBO
    m_fbo.end();

    // Take a cloned copy of selected elements, and a copy of the current transform
    for (auto const& id : selectedIds) {
        m_elements.push_back(scene.GetElement(id)->Clone());
    }

    if (nullptr == m_mask) {
        // Open a file dialog and let the user choose a image file
        std::string filePath;
        if (datUtilities::OpenFileDialog(filePath, true/*fileMustExist*/)) {

            m_mask = std::make_unique<ofImage>();
            if (!m_mask->load(filePath))
                m_mask = nullptr;
        }
    }

    if (nullptr != m_mask) {

        m_shader.load(datUtilities::GetAssetsFolder().append("composition_330_vs.glsl"),
            datUtilities::GetAssetsFolder().append("composition_330_fs.glsl"));

        GetRenderer().SetNeverDraw(selectedIds);
        assert(!m_elements.empty());
        applyTexture();
    }
}


void datAddTextureTool::onExitTool() {

    // Commit changes to elements
    GetRenderer().GetScene().UpdateElements(std::move(m_elements));
    GetRenderer().ClearNeverDraw();

    m_shader.unload();
}

void datAddTextureTool::applyTexture() {

#if 0
    for (auto const& geometry : m_elements) {
        if (geometry->GetType() == datGeometry::GeometryType::Image) {
            datImage image = geometry->GetAsImage();
            m_mask->resize(image.m_width, image.m_height);
            m_fbo.allocate(image.m_width, image.m_height);
            m_fbo.begin();
            m_shader.begin();

            m_shader.setUniformTexture("mask", m_mask->getTexture(), 1);
            m_shader.setUniformTexture("image", image.m_image.getTexture(), 2);

            image.m_image.draw(0, 0);

            m_shader.end();
            m_fbo.end();
            ofImage img;
            ofPixels pixels;
            m_fbo.readToPixels(pixels);
            img.setFromPixels(pixels);
            img.draw(img.getWidth(), 0);

            geometry->GetAsImage().m_image = img;
        }
    }
#endif

    m_mask = nullptr;
}

void datAddTextureTool::onDraw() {
    _ExitTool();
}
