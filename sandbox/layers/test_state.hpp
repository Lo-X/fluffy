#pragma once

#include "../../src/platform/glfw/src/imgui_impl_glfw.h"
#include <fluffy/api/modules.hpp>
#include <fluffy/fluffy_core.hpp>
#include <fluffy/fluffy_ecs.hpp>
#include <fluffy/game/camera_controller.hpp>
#include <fluffy/graphics/camera.hpp>
#include <fluffy/graphics/render_command.hpp>
#include <fluffy/graphics/renderer.hpp>
#include <fluffy/graphics/shader.hpp>
#include <fluffy/graphics/texture.hpp>
#include <fluffy/graphics/transformable.hpp>
#include <fluffy/graphics/vertex.hpp>
#include <fluffy/input/input.hpp>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <opengl.hpp>

class TestState : public State<TestState>
{
public:
    TestState() : cameraController(1280.f / 720.f) {}

    void initialize() override
    {
        RenderCommand::setClearColor(Color::fromInt8(204, 51, 204, 255));

        // Shader
        shader = Shader::create();
        shader->loadFromFile("assets/shaders/base.vertex.shader", "assets/shaders/base.fragment.shader");
//        shader->loadFromFile("assets/shaders/sprite.vertex.shader", "assets/shaders/sprite.fragment.shader");

        flatColorShader = Shader::create();
        flatColorShader->loadFromFile("assets/shaders/flat_color.vertex.shader", "assets/shaders/base.fragment.shader");

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        vaTriangle = VertexArray::create();
        float vertices[3*7] = {
          0.f, 0.5f, -0.10f, 0.8f, 0.1f, 0.1f, 1.f,
          0.5f, -0.5f, -0.10f, 0.1f, 0.8f, 0.1f, 1.f,
          -0.5f, -0.5f, -0.10f, 0.1f, 0.1f, 0.8f, 1.f,
        };
        Ref<VertexBuffer> vbTriangle = VertexBuffer::create(vertices, sizeof(vertices));
        vbTriangle->setLayout({
            { ShaderDataType::Vector3f, "aPos" },
            { ShaderDataType::Vector4f, "aColor" },
        });
        std::uint32_t indices[3] = { 0, 1, 2 };
        Ref<IndexBuffer> ibTriangle = IndexBuffer::create(indices, 3);
        vaTriangle->addVertexBuffer(vbTriangle);
        vaTriangle->setIndexBuffer(ibTriangle);


        vaSquare = VertexArray::create();
        float verticesSquare[4*3] = {
          0.75f, -0.75f, 0.0f,
          0.75f, 0.75f, 0.0f,
          -0.75f, -0.75f, 0.0f,
          -0.75f, 0.75f, 0.0f,
        };
        Ref<VertexBuffer> vbSquare = VertexBuffer::create(verticesSquare, sizeof(verticesSquare));
        vbSquare->setLayout({
                              { ShaderDataType::Vector3f, "aPos" },
                            });
        std::uint32_t indicesSquare[6] = { 0, 1, 2, 2, 3, 1 };
        Ref<IndexBuffer> ibSquare = IndexBuffer::create(indicesSquare, 6);
        vaSquare->addVertexBuffer(vbSquare);
        vaSquare->setIndexBuffer(ibSquare);

        // My texture
        texture = Texture2D::create("assets/textures/alpaca.png");
        texture->setRepeat(RepeatType::Repeat);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.KeyMap[ImGuiKey_Tab] = (int)Keyboard::Key::Tab;
        io.KeyMap[ImGuiKey_LeftArrow] = (int)Keyboard::Key::Left;
        io.KeyMap[ImGuiKey_RightArrow] = (int)Keyboard::Key::Right;
        io.KeyMap[ImGuiKey_UpArrow] = (int)Keyboard::Key::Up;
        io.KeyMap[ImGuiKey_DownArrow] = (int)Keyboard::Key::Down;
        io.KeyMap[ImGuiKey_PageUp] = (int)Keyboard::Key::PageUp;
        io.KeyMap[ImGuiKey_PageDown] = (int)Keyboard::Key::PageDown;
        io.KeyMap[ImGuiKey_Home] = (int)Keyboard::Key::Home;
        io.KeyMap[ImGuiKey_End] = (int)Keyboard::Key::End;
        io.KeyMap[ImGuiKey_Insert] = (int)Keyboard::Key::Insert;
        io.KeyMap[ImGuiKey_Delete] = (int)Keyboard::Key::Delete;
        io.KeyMap[ImGuiKey_Backspace] = (int)Keyboard::Key::Backspace;
        io.KeyMap[ImGuiKey_Space] = (int)Keyboard::Key::Space;
        io.KeyMap[ImGuiKey_Enter] = (int)Keyboard::Key::Enter;
        io.KeyMap[ImGuiKey_Escape] = (int)Keyboard::Key::Escape;
        io.KeyMap[ImGuiKey_KeyPadEnter] = (int)Keyboard::Key::NumPadEnter;
        io.KeyMap[ImGuiKey_A] = (int)Keyboard::Key::Q;
        io.KeyMap[ImGuiKey_C] = (int)Keyboard::Key::C;
        io.KeyMap[ImGuiKey_V] = (int)Keyboard::Key::V;
        io.KeyMap[ImGuiKey_X] = (int)Keyboard::Key::X;
        io.KeyMap[ImGuiKey_Y] = (int)Keyboard::Key::Y;
        io.KeyMap[ImGuiKey_Z] = (int)Keyboard::Key::W;

        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)getContext()->video->getWindow()->getNativeWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 130");
    }

    void terminate() override
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void fixUpdate(Time dt) override
    {
//        if (Input::isKeyPressed(Keyboard::Key::W)) {
//            squareTransform.translate({0.f, 1.f * dt.seconds(), 0.f});
//        } else if (Input::isKeyPressed(Keyboard::Key::S)) {
//            squareTransform.translate({0.f, -1.f * dt.seconds(), 0.f});
//        }
//
//        if (Input::isKeyPressed(Keyboard::Key::A)) {
//            squareTransform.translate({-1.f * dt.seconds(), 0.f, 0.f});
//        } else if (Input::isKeyPressed(Keyboard::Key::D)) {
//            squareTransform.translate({ 1.f * dt.seconds(), 0.f, 0.f});
//        }

        // Update camera
        cameraController.update(dt);

        // ImGUI Stuff
        auto definition = getContext()->video->getWindow()->getDefinition();
        ImGuiIO& io = ImGui::GetIO();
        io.DeltaTime = dt.seconds();
        io.DisplaySize = {definition.width * 1.f, definition.height * 1.f};

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Settings");
            ImGui::ColorEdit4("Square color", glm::value_ptr(squareColor));
            ImGui::End();
        }
    }

    void render(Time dt) override
    {
        Renderer::beginScene(cameraController.getCamera());

        flatColorShader->enable();
        flatColorShader->bindUniform("u_Color", squareColor);
        Renderer::draw(vaSquare, flatColorShader, transformSquare.getTransformMatrix());
        Renderer::draw(vaTriangle, shader);

        Renderer::endScene();
//        Renderer::flush();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void onEvent(Event& event) override
    {
        // Update camera
        cameraController.onEvent(event);

        if (event.type == Fluffy::Event::MouseButtonPressed) {
            auto position = Input::getMousePosition();
            FLUFFY_LOG_DEBUG("Mouse button pressed: {} (at {})", EnumNames::MouseButton[(int)event.mouseButton.button], position);
        }
    }

private:
    OrthographicCameraController cameraController;
    Ref<Shader> shader;
    Ref<Shader> flatColorShader;
    Ref<Texture2D> texture;
    Ref<VertexArray> vaTriangle;
    Ref<VertexArray> vaSquare;
    Transformable transformSquare;
    Vector4f squareColor = {.2f, .8f, .43f, 1.f};
};