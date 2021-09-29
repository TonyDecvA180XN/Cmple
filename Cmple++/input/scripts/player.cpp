double x, y, angle;
int data;

Create{
    x = 0;
    y = 0;
    angle = 0;
}

Destroy{

}

Update{
    angle += 0.01;
    if(keyboard(KB_A))
        sound_play(back_music);
    if(keyboard(KB_B))
        sound_stop(back_music);
    if(keyboard(KB_UP))
        y += 0.001;
    if(keyboard(KB_DOWN))
        y -= 0.001;
    if(keyboard(KB_LEFT))
        x -= 0.001;
    if(keyboard(KB_RIGHT))
        x += 0.001;
}

Draw3D{
    draw_model(pawnW, x, 0.0, y, angle, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0);
}

Draw2D{
    draw_sprite(gatling, 200.0, 200.0, 45.0, 96.0, 96.0, 1.0, 1.0, 1.0);
}
