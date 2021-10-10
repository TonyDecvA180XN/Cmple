double x, y, angle;

Create {
    x = 1.0;
    y = 0.0;
    angle = 0.0;

    pawn p = create_object_pawn();
    p&idx = 0;
    pawn p2 = p;
    p2&idx = -1;

    pawn t[10];
    for (int i = 1; i <= 10; i++) {
        t[i] = create_object_pawn();
        t[i]&idx = i;
    }

    destroy_object_pawn(t[5]);
    t[5] = create_object_pawn();
    t[5]&idx = 11;
    std::cout << t[5] << std::endl;

    sound_play(back_music);
}

Destroy {

}

Update {
    if (keyboard(KB_A))
        sound_play(back_music);

    if (keyboard(KB_B))
        sound_stop(back_music);

    if (mouse_pressed(MB_LEFT))
        x = -x;
    if (mouse_released(MB_RIGHT))
        y = -y;

    if (mouse(MB_MIDDLE))
        angle -= 0.1;
    else
        angle += 0.1;

    if (keyboard(KB_UP))
        x -= 0.01;
    if (keyboard(KB_DOWN))
        x += 0.01;
    if (keyboard(KB_LEFT))
        y += 0.01;
    if (keyboard(KB_RIGHT))
        y -= 0.01;

    if (keyboard_released(KB_C))
        std::swap(x, y);

    if (keyboard_pressed(KB_D))
        set_frame_per_second(10.0);
    if (keyboard_released(KB_D))
        set_frame_per_second(100.0);

    if (keyboard_pressed(KB_SPACE))
        end_program();
}

Draw3D {
    set_camera_position_by_look_at(5.0, 3.0, 0.0, 0.0, 0.5, 0.0);
    // set_camera_position_by_angles(5.0, 3.0, 0.0, 0.0, 1.0, 0.0, 180.0, -30.0);

    set_exposure(1.0);

    set_directional_light_direction(0.0, 10.0, -1.0);
    set_directional_light_color(1.0, 1.0, 1.0);

    set_point_light_position(0, -x, 0.0, -y);
    set_point_light_color(0, 0.2, 0.2, 1.0);

    set_spot_light_position(x, 0.0, y);
    set_spot_light_color(1.0, 0.2, 0.2);
    set_spot_light_direction(-x, 0.5, -y);
    set_spot_light_angle(20.0, 30.0);

    draw_model(pawnW, 0.0, 0.0, 0.0, angle, 0.0, 1.0, 0.0, 3.0, 3.0, 3.0);

    draw_model(pawnW, x, 0.0, y, angle, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0);
}

Draw2D {
    double pi = 2.0 * acos(0.0);

    draw_text("It's cmple!", FT_ARIAL, 50.0, 50.0, 0.0, 1.0, 32.0, 1.0, 0.3, 0.3);
    draw_text("Ra%^&bW\\&~a\"b\'a`fa)(sg{}/", FT_CALIBRI, 300.0, 300.0, angle, 1.0, 32.0, 0.3, 0.3, 1.0);
    draw_text(std::to_string(mouse_x()), FT_TIMES_NEW_ROMAN, 100.0, 500.0, 0.0, 1.0, 24.0, 0.3, 1.0, 0.3);
    draw_text(std::to_string(mouse_y()), FT_TIMES_NEW_ROMAN, 100.0, 550.0, 0.0, 2.0, 32.0, 0.3, 1.0, 1.0);
    draw_sprite(gatling, 600.0, 400.0, 45.0, 96.0, 96.0,
                sin(angle / 180.0 * pi) / 2.0 + 0.5,
                sin(angle / 180.0 * pi + pi / 3.0) / 2.0 + 0.5,
                sin(angle / 180.0 * pi + 2.0 * pi / 3.0) / 2.0 + 0.5);

    if (sound_is_playing(back_music))
        draw_text("Music: ON", FT_ARIAL, 500.0, 30.0, 0.0, 1.0, 32.0, 1.0, 1.0, 0.3);
    else
        draw_text("Music: OFF", FT_ARIAL, 500.0, 30.0, 0.0, 1.0, 32.0, 1.0, 0.3, 1.0);
}
