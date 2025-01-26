**Setup and Run Instructions**

  Clone the repository:
  
    git clone https://github.com/Bishmit/RigidBodyPhysicsEngine.git
    cd project-name

Configure and build with CMake from visual studio for window: 

    mkdir build && cd build
    cmake .. -G "Visual Studio 17 2022"
    Open the generated `.sln` file in Visual Studio, set the project as the startup project, then build and run it.


On Linux:

After Cloning install the required dependecies(if not already installed):

      sudo apt update
      sudo apt install libsfml-dev cmake g++

Configure and build with CMake:

    mkdir build && cd build
    cmake ..
    make 
    ./bin/RigidBodyPhysicsEngine

Notes

    -Ensure that the CMake and C/C++ extensions are installed in VS Code. These are essential for configuring and building the project.
    -Set g++ (or an appropriate compiler) as the default in your system and ensure it's accessible in your PATH.
    -Configuring the project in VS Code on Windows follows the same steps as on Linux, with minor adjustments if needed for paths or environment.
    -CMake will automatically fetch and configure the required libraries (e.g., SFML, ImGui) if the CMakeLists.txt file is set up properly.
    -Update paths, environment variables, or commands based on your specific configuration or system setup.
