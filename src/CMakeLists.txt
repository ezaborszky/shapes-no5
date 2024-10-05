add_executable(shapes main.cpp Game.cpp Entity.cpp EntityManager.cpp)
target_link_libraries(shapes PRIVATE ImGui-SFML::ImGui-SFML)
