# Cmple++ Manual

## <a name="Specification"></a> Specification

### <a name="Description"></a> Description
    
The main purpose of **Cmple++** program is to facilitate writing programs using graphic and interaction API-s. The program abstract the internal API-s and the architecture from user and present the unified API for all his purposes.
        
#### <a name="How_to_use_it"></a> How to use it
The **Cmple++** program expects as input three directories:

1. **User input directory**. User writes a program in **user input directory**..

2. **Internal input directory**. The **internal input directory** has to be downloaded with the **Cmple++** program. Make sure to download the correct version.

3. **Output directory**. The resulting project files will be saved in **output directory**.

After successful parsing the user will have the source code and all resource files in **output directory**. It is his decision how to compile it. There are following ways:

* If user works with **GNU GCC 64-bit** compiler, he can use corresponding integrated execution flags.

* Otherwise user can use **CMake** to configure the project file for his IDE.

#### <a name="Execution_flags"></a> Execution flags

The **Cmple++** program supports the following set of execution arguments:

1. **input=\<directory\>**. This flag specifies the **user input directory**. By default it is **input**.

2. **const_input=\<directory\>**. This flag specifies the **internal input directory**. By default it is <b>const_input</b>.

3. **to_compile=\<directory\>**. This flag specifies the **output directory**. By default it is **to_compile**.

4. **gcc_create_batch**. With this flag the parser will create **batch** file for compilation program using **GNU GCC** compiler.

5. **gcc_auto_execute**. With this flag the parser will create **batch** file for compilation program using **GNU GCC** compiler and execute it.

#### <a name="Supported_compilers"></a> Supported compilers

Both **parser** and **engine** support following compilers:

* GNU GCC
* Visual C++
* Clang

Only 64-bit compilers are supported.

#### <a name="Supported_operating_systems"></a> Supported operating systems

The **parser** supports following operating systems:

* Windows
* Unix

The **engine** supports following operating systems:

* Windows

### <a name="Input_format"></a> Input format

This is the description of input. Read it before starting using **Cmple++**.

#### <a name="User_input_directory"></a> User input directory

The **user input directory** has to contain following folders:
* Scripts
* Sprites
* Models
* Sounds

#### <a name="Class_scripts"></a> Class scripts

Each file **\<name\>.cpp** represents the class **name**. It has to be placed in **scripts** subdirectory. The file has to contain the following function:

* **Create**. This function is called once object is created.
* **Destroy**. This function is called once object is destroyed.
* **Update**. This function is called while each update iteration.
* **Draw3D**. This function is called while each render 3D iteration. This is the only place, where user can call functions related to 3D rendering.
* **Draw2D**. This function is called while each render 2D iteration. This is the only place, where user can call functions related to 2D rendering.

These function are written in form **<function\> {...}**. No other functions has to be written. Also file may contain class variables. All code except the function declarations has to be written in accordance to **C++ standard**. View example to make it more clear.

#### <a name="Creation_code_script"></a> Creation code script

**Creation code script** is a file **creation_code.cpp**, which has to be in **scripts** subdirectory. In comparison to class files, it can't contain functions, but can contain local variables. This script is executed at start of the program and has to be used, to create objects of classes. This is the only place, where user can change the name and resolution of window.

#### <a name="Sprites"></a> Sprites

Sprite has to be placed in **Sprites** subdirectory. It can have one of following extensions:
* **.jpg**
* **.png**
* **.bmp**
* **.tga**

There might be also undocumented support for some other extensions.

#### <a name="Models"></a> Models

Model has to be placed in **models** subdirectory. It can have only **.obj** extension. The **.obj** specification is supported only partially. Also there are some **.obj** features, which can be successfully read, but can't be used in rendering due to simple graphics engine. **Important**: some models, downloaded from the Internet, have absolute paths to components. In this case, user has to deal with it by his own.

#### <a name="Sounds"></a> Sounds

Sound has to be placed in **sounds** subdirectory. It can have one of following extensions:
* **.mp3**
* **.ogg**
* **.wav**

There might be also undocumented support for some other extensions. Note: the loading of **.mp3** and **.ogg** extensions is relatively slow.

### <a name="Parser"></a> Parser

This is advanced explanation of algorithm used in parser. It is not obligatory to know it to start using **Cmple++**.

#### <a name="Class_type"></a> Class type

**Cmple++** introduces the following variables for every class in files **classes_implementation.h** and **classes_implementation.cpp**:
* **using \<class_name\>_typename = int;**
* **std::map\<int, \<class_name\>\*\> \<class_name\>_container;**
* **int \<class_name\>_object_number = 0;**

Every class type variable is parsed into type **\<class_name\>_typename**. If after a class **\<class_name\>** variable **\<var\>** there is **&**, then these units are parsed to **\<class_name\>_container[\<var\>]-\>**.

#### <a name="Class_API"></a> Class API

**Cmple++** introduces the following functions for every class in files **classes_implementation.h** and **classes_implementation.cpp**:
* **\<class_name\>_typename create_object_\<class_name\>();** This function allocates new object of class **\<class_name\>** and returns it identifier.
* **void destroy_object_\<class_name\>(\<class_name\>_typename id);** This function deallocated the object of class **\<class_name\>** with given identifier. This identifier will never be given to any new allocated object of this class.

These functions are used to create and destroy objects of user classes.

#### <a name="Input_file_parsing"></a> Input file parsing

Input file has to contain a corresponding class. This class should not be declared according to **C++ standard**. Instead, the file has to contain variables and function in global scope. Only following functions has to be in the file:
* **Create**
* **Destroy**
* **Update**
* **Draw3D**
* **Draw2D**

This function has to be declared in form **\<function\> {...}**. Also all access to variables of classes has to be done through operator **&** instead of **.** or **-\>**, as they has to be operated as class variables. The parser detects the scope of variables while checking, if a variable has a class type. There are no other restrictions, and the code has to be written in accordance to <b>C++ standard</b>. The parser creates both **source** and **header** files. There also has to be a **creation_code.cpp** file in **user input directory**. This code is parsed as a single function and can't have any function in it.

#### <a name="Output_files"></a> Output files

The parser create the following set of files in **output directory**:
* **\<class_name\>.cpp** - the source file for every input class, which is compiled separately.
* **\<class_name\>.h** - the header file for every input class, which is compiled separately.
* **creation_code.h** - the header file for creation code file, which is included in corresponding place.
* **classes_implementation.cpp** - the source file with API of input classes, which is compiled separately.
* **classes_implementation.h** - the header file with API of input classes, which is compiled separately.
* **files_load.h** - the header file with loading sprites and models, which is included in corresponding place.
* **files_load_audio.h** - the header file with loading sounds, which is included in corresponding place.
* **files_update.h** - the header file with call update function of input classes, which is included in corresponding place.
* **files_display3d.h** - the header file with call **Draw3D** function of input classes, which is included in corresponding place.
* **files_display2d.h** - the header file with call **Draw2D** function of input classes, which is included in corresponding place.

### <a name="Engine"></a> Engine

This is advanced explanation of algorithm used in parser. It is not obligatory to know it to start using **Cmple++**.

#### <a name="Graphic_libraries"></a> Graphic libraries

The engine renders using [OpenGL version 3.3 core profile](https://www.khronos.org/registry/OpenGL/specs/gl/glspec33.core.pdf). It also uses following libraries:
* [GLFW](https://www.glfw.org/) for using operation system API for creating windows and checking input.
* [GLAD](https://glad.dav1d.de/) as a loading library.
* [stb_image](https://github.com/nothings/stb) for loading images.

#### <a name="Graphic_model"></a> Graphic model

The engine uses following technics:
* [Blinn-Phong](https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model)
* [High Dynamic Range Imaging (HDR)](https://ru.wikipedia.org/wiki/High_Dynamic_Range_Imaging)
* [Gamma Correction](https://en.wikipedia.org/wiki/Gamma_correction)

Also engine supports following types of lights:
* Directional light
* Point light
* Spot light

The engine supports as a material only the **diffuse map**.

#### <a name="Audio"></a> Audio

The engine uses [Audiere](http://audiere.sourceforge.net/) for audio processing.

#### <a name="Resource_support"></a> Resource support

The engine has following classes for support the input resources:
* **Sprite**. Loads image using [stb_image](#Graphic libraries) and renders it.
* **Model**. Loads **.obj** model using self-written parser and renders it.
* **Sound**. Loads sound using [Audiere](#Audio) parser and calls it to play the sound.
* **Shader**. Loads vertex, fragment and geometric shaders written on [GLSL version 330](https://www.khronos.org/opengl/wiki/Core_Language_(GLSL))
* **Font**. Loads **.fnt** font using self-written parser and [stb_image](#Graphic_libraries) and renders it.
