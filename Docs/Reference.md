# Cmple++ API Reference

## <a name="Navigation"></a>Navigation
1. [Class interaction](#Class_interaction)
    1. [Function create_object_\<class_name\>](#Function_create_object_class_name)
    2. [Function destroy_object_\<class_name\>](#Function_destroy_object_class_name)
    3. [Class access operator &](#Class_access_operator_&)

2. [Keyboard](#Keyboard)
    1. [Keyboard key_type](#Keyboard_key_type)
    2. [Function keyboard](#Function_keyboard)
    3. [Function keyboard_pressed](#Function_keyboard_pressed)
    4. [Function keyboard_released](#Function_keyboard_released)

3. [Mouse](#Mouse)
    1. [Mouse button type](#Mouse_button_type)
    2. [Function mouse](#Function_mouse)
    3. [Function mouse_pressed](#Function_mouse_pressed)
    4. [Function mouse_released](#Function_mouse_released)
    5. [Function mouse_x](#Function_mouse_x)
    6. [Function mouse_y](#Function_mouse_y)

4. [Program control](#Program_control)
    1. [Function set_resolution](#Function_set_resolution)
    2. [Function set_window_name](#Function_set_window_name)
    3. [Function set_frame_per_second](#Function_set_frame_per_second)
    4. [Function end_program](#Function_end_program)

5. [Camera](#Camera)
    1. [Function set_camera_position_by_look_at](#Function_set_camera_position_by_look_at)
    2. [Function set_camera_position_by_angles](#Function_set_camera_position_by_angles)

6. [Light](#Light)
    1. [Function set_exposure](#Function_set_exposure)
    2. [Function set_directional_light_direction](#Function_set_directional_light_direction)
    3. [Function set_directional_light_color](#Function_set_directional_light_color)
    4. [Function set_point_light_position](#Function_set_point_light_position)
    5. [Function set_point_light_color](#Function_set_point_light_color)
    6. [Function set_spot_light_position](#Function_set_spot_light_position)
    7. [Function set_spot_light_color](#Function_set_spot_light_color)
    8. [Function set_spot_light_direction](#Function_set_spot_light_direction)
    9. [Function set_spot_light_angle](#Function_set_spot_light_angle)

7. [Render](#Render)
    1. [Font type](#Font_type)
    2. [Function draw_text](#Function_draw_text)
    3. [Function draw_sprite](#Function_draw_sprite)
    4. [Function draw_model](#Function_draw_model)

8. [Sound](#Sound)
    1. [Function sound_play](#Function_sound_play)
    2. [Function sound_stop](#Function_sound_stop)
    3. [Function sound_is_playing](#Function_sound_is_playing)

## <a name="API"></a> API

### <a name="Class_interaction"></a> Class interaction

#### <a name="Function_create_object_class_name"></a> Function create_object_\<class_name\>

**\<class_name\>_typename create_object_\<class_name\>();** The function creates the object of class **\<class_name\>** and returns its identifier.

[Navigation](#Navigation)

#### <a name="Function_destroy_object_class_name"></a> Function destroy_object_\<class_name\>

**void destroy_object_\<class_name\>(\<class_name\>_typename id);** The function destroys the object of class **\<class_name\>** with identifier id.

[Navigation](#Navigation)

#### <a name="Class_access_operator_&"></a> Class access operator &

The access to variable of **\<class_name\>_typename** has to be made through the operator **&**. Example: A a; a&x = 5; B b[5]; b[1]&y = 6.

[Navigation](#Navigation)

### <a name="Keyboard"></a> Keyboard

#### <a name="Keyboard_key_type"></a> Keyboard key type

The keyboard keys have type **cmple_keyboard_key** and defined in form **KB_\<key\>**. Example: **KB_SPACE**.

[Navigation](#Navigation)

#### <a name="Function_keyboard"></a> Function keyboard

**bool keyboard(cmple_keyboard_key key);** The function returns if the **key** is pressed.

[Navigation](#Navigation)

#### <a name="Function_keyboard_pressed"></a> Function keyboard_pressed

**bool keyboard_pressed(cmple_keyboard_key key);** The function returns if the **key** was currently pressed.

[Navigation](#Navigation)

#### <a name="Function_keyboard_released"></a> Function keyboard_released

**bool keyboard_released(cmple_keyboard_key key);** The function returns if the **key** was currently released.

[Navigation](#Navigation)

### <a name="Mouse"></a> Mouse

#### <a name="Mouse_button_type"></a> Mouse button type

The mouse buttons have type **cmple_mouse_button** and defined in form **MB_\<key\>**. Example: **MB_LEFT**.

[Navigation](#Navigation)

#### <a name="Function_mouse"></a> Function mouse

**bool mouse(cmple_mouse_button button);** The function returns if the **button** is pressed.

[Navigation](#Navigation)

#### <a name="Function_mouse_pressed"></a> Function mouse_pressed

**bool mouse_pressed(cmple_mouse_button button);** The function returns if the **button** was currently pressed.

[Navigation](#Navigation)

#### <a name="Function_mouse_released"></a> Function mouse_released

**bool mouse_released(cmple_mouse_button button);** The function returns if the **button** was currently released.

[Navigation](#Navigation)

#### <a name="Function_mouse_x"></a> Function mouse_x

**int mouse_x();** The function returns the x coordinate of cursor in pixels relative to upper left corner of window.

[Navigation](#Navigation)

#### <a name="Function_mouse_y"></a> Function mouse_y

**int mouse_y();** The function returns the y coordinate of cursor in pixels relative to upper left corner of window.

[Navigation](#Navigation)

### <a name="Program_control"></a> Program control

#### <a name="Function_set_resolution"></a> Function set_resolution

**void set_resolution(unsigned int width, unsigned int height);** The function sets the sizes of window to **width** and **height**. The function has to be called in creation code or in Create function of class, whose object was created during creation code. Otherwise, the function will not change anything.

[Navigation](#Navigation)

#### <a name="Function_set_window_name"></a> Function set_window_name

**void set_window_name(std::string name);** The function sets the title of window to **name**. The function has to be called in creation code or in create function of class, whose object was created during creation code. Otherwise, the function will not change anything.

[Navigation](#Navigation)

#### <a name="Function_set_frame_per_second"></a> Function set_frame_per_second

**void set_frame_per_second(double fps);** The function sets the frame per second of program to **fps**. By default the fps is 100.

[Navigation](#Navigation)

#### <a name="Function_end_program"></a> Function end_program

**void end_program();** The function ends program at the end of current iteration. **Important**: this function does not call Destroy function of objects.

[Navigation](#Navigation)

### <a name="Camera"></a> Camera

#### <a name="Function_set_camera_position_by_look_at"></a> Function set_camera_position_by_look_at

**void set_camera_position_by_look_at(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);** The function sets the position of camera such that it is in point (**posX**, **posY**, **posZ**), looks at point (**targetX**, **targetY**, **targetZ**) and its upper vector is (0, 1, 0).

[Navigation](#Navigation)

#### <a name="Function_set_camera_position_by_angles"></a> Function set_camera_position_by_angles

**void set_camera_position_by_angles(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);** The function sets the position of camera such that it is in point (**posX**, **posY**, **posZ**), has upper vector (**upX**, **upY**, **upZ**) and corresponding **pitch** and **yaw**. The **pitch** and **yaw** are measured in degrees.

[Navigation](#Navigation)

### <a name="Light"></a> Light

#### <a name="Function_set_exposure"></a> Function set_exposure

**void set_exposure(float exposure);** The function sets the **exposure** of light. By default it is recommended to use exposure = 1. The function has to be called in **Draw3D** function of class. Otherwise, the function will not change anything.

[Navigation](#Navigation)

#### <a name="Function_set_directional_light_direction"></a> Function set_directional_light_direction

**void set_directional_light_direction(float dirX, float dirY, float dirZ);** The function sets the direction of directional light to (**dirX**, **dirY**, **dirZ**). The function has to be called in **Draw3D** function of class. Otherwise, the function will not change anything.

[Navigation](#Navigation)

#### <a name="Function_set_directional_light_color"></a> Function set_directional_light_color

**void set_directional_light_color(float colorRed, float colorGreen, float colorBlue);** The function sets the color of directional light to (**colorRed**, **colorGreen**, **colorBlue**). The function has to be called in **Draw3D** function of class. Otherwise, the function will not change anything.

[Navigation](#Navigation)

#### <a name="Function_set_point_light_position"></a> Function set_point_light_position

**void set_point_light_position(int index, float posX, float posY, float posZ);** The function sets the position of point light with corresponding **index** to (**posX**, **posY**, **posZ**). The index has to be from 0 to 15. The function has to be called in **Draw3D** function of class. Otherwise, the function will not change anything.

[Navigation](#Navigation)

#### <a name="Function_set_point_light_color"></a> Function set_point_light_color

**void set_point_light_color(int index, float colorRed, float colorGreen, float colorBlue);** The function sets the color of point light with corresponding **index** to (**colorRed**, **colorGreen**, **colorBlue**). The index has to be from 0 to 15. The function has to be called in **Draw3D** function of class. Otherwise, the function will not change anything.

[Navigation](#Navigation)

#### <a name="Function_set_spot_light_position"></a> Function set_spot_light_position

**void set_spot_light_position(float posX, float posY, float posZ);** The function sets the position of spot light to (**posX**, **posY**, **posZ**). The function has to be called in **Draw3D** function of class. Otherwise, the function will not change anything.

[Navigation](#Navigation)

#### <a name="Function_set_spot_light_color"></a> Function set_spot_light_color

**void set_spot_light_color(float colorRed, float colorGreen, float colorBlue);** The function sets the color of spot light to (**colorRed**, **colorGreen**, **colorBlue**). The function has to be called in **Draw3D** function of class. Otherwise, the function will not change anything.

[Navigation](#Navigation)

#### <a name="Function_set_spot_light_direction"></a> Function set_spot_light_direction

**void set_spot_light_direction(float dirX, float dirY, float dirZ);** The function sets the direction of spot light to (**dirX**, **dirY**, **dirZ**). The function has to be called in **Draw3D** function of class. Otherwise, the function will not change anything.

[Navigation](#Navigation)

#### <a name="Function_set_spot_light_angle"></a> Function set_spot_light_angle

**void set_spot_light_angle(float angleInner, float angleOuter);** The function sets the angle of full intensity of spot light to **angleInner** and angle of decreasing from full to zero intensity to **angleOuter**. The **angleInner** and **angleOuter** are measured in degrees. The function has to be called in **Draw3D** function of class. Otherwise, the function will not change anything.

[Navigation](#Navigation)

### <a name="Render"></a> Render

#### <a name="Font_type"></a> Font type

The font have type **cmple_font** and defined in form **FT_\<font\>**. Only 3 fonts are available:
* FT_ARIAL
* FT_CALIBRI
* FT_TIMES_NEW_ROMAN

[Navigation](#Navigation)

#### <a name="Function_draw_text"></a> Function draw_text

**void draw_text(std::string text, cmple_font font, float posX, float posY, float rotateAngle, float scaleX, float sizeY, float colorRed, float colorGreen, float colorBlue);** The function renders the given **text**, using given **font**, in point (**posX**, **posY**), rotated to **rotateAngle**, scaled width to **scaleX**, with size **sizeY**, relatively to upper left corner, with color (**colorRed**, **colorGreen**, **colorBlue**). The **rotateAngle** is measured in degrees. The function has to be called in **Draw2D** function of class. Otherwise, the function will not change anything.

[Navigation](#Navigation)

#### <a name="Function_draw_sprite"></a> Function draw_sprite

**void draw_sprite(Sprite sprite, float posX, float posY, float rotateAngle, float scaleX, float scaleY, float colorRed, float colorGreen, float colorBlue);** The function renders the given **sprite**, in point (**posX**, **posY**), rotated to **rotateAngle**, scaled to (**scaleX**, **scaleY**), relatively to upper left corner, with color (**colorRed**, **colorGreen**, **colorBlue**). The **rotateAngle** is measured in degrees. The function has to be called in **Draw2D** function of class. Otherwise, the function will not change anything.

[Navigation](#Navigation)

#### <a name="Function_draw_model"></a> Function draw_model

**void draw_model(Model model, float posX, float posY, float posZ, float rotateAngle, float rotateX, float rotateY, float rotateZ, float scaleX, float scaleY, float scaleZ);** The function renders the given **model**, in point (**posX**, **posY**, **posZ**), rotated to **rotateAngle** relative to axis (**rotateX**, **rotateY**, **rotate**), scaled to (**scaleX**, **scaleY**, **scaleZ**). The **rotateAngle** is measured in degrees. The function has to be called in **Draw3D** function of class. Otherwise, the function will not change anything.

[Navigation](#Navigation)

### <a name="Sound"></a> Sound

#### <a name="Function_sound_play"></a> Function sound_play

**void sound_play(Sound sound);** The function plays the **sound**.

[Navigation](#Navigation)

#### <a name="Function_sound_stop"></a> Function sound_stop

**void sound_stop(Sound sound);** The function stops the **sound**.

[Navigation](#Navigation)

#### <a name="Function_sound_is_playing"></a> Function sound_is_playing

**bool sound_is_playing(Sound sound);** The function returns if the **sound** is playing.

[Navigation](#Navigation)
