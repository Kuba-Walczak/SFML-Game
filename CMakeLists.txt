cmake_minimum_required(VERSION 3.29.6)

project(2DGame)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 11.1.4
)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
)

FetchContent_MakeAvailable(fmt SFML)
add_executable(Main
        Main.cpp
        Player.cpp
        Player.h
        View.cpp
        View.h
        Collider.cpp
        Collider.h
        Weapons/Weapon.cpp
        Weapons/Weapon.h
        Enemies/Enemy.cpp
        Enemies/Enemy.h
        Weapons/Projectile.cpp
        Weapons/Projectile.h
        Weapons/Types/Debugger.cpp
        Weapons/Types/Debugger.h
        Weapons/Types/CollisionTrigger.cpp
        Weapons/Types/CollisionTrigger.h
        Weapons/Types/ThreadManager.cpp
        Weapons/Types/ThreadManager.h
        Enemies/Types/SyntaxError.cpp
        Enemies/Types/SyntaxError.h
        Enemies/Types/ExceptionThrower.cpp
        Enemies/Types/ExceptionThrower.h
        Enemies/Types/Error.cpp
        Enemies/Types/Error.h
        Enemies/Types/Knowledge.cpp
        Enemies/Types/Knowledge.h
        Effect.cpp
        Effect.h
        Collision.cpp
        Collision.h
        Utility/RNG.cpp
        Utility/RNG.h
        Utility/Updatable.h
        Utility/Usable.h
        Utility/Updatable.cpp
        Utility/Usable.cpp
        TileCover.cpp
        TileCover.h
        Menu.cpp
        Menu.h
)
target_link_libraries(Main fmt::fmt SFML::Graphics)