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
        m_geometries.push_back(scene.GetGeometry(id)->Clone());
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
        assert(!m_geometries.empty());
        applyTexture();
    }
}


void datAddTextureTool::onExitTool() {

    // Commit changes to elements
    GetRenderer().GetScene().UpdateMultipleGeometries(std::move(m_geometries));
    GetRenderer().ClearNeverDraw();

    m_shader.unload();
}

void datAddTextureTool::applyTexture() {

    for (auto const& geometry : m_geometries) {
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

    m_mask = nullptr;
}

void datAddTextureTool::onDraw() {

    //&&AG needswork. I need to fix onStartTool so the tool can exit inside that method.
    // for now, exit tool on first draw call to avoid any issues
    _ExitTool();
}
