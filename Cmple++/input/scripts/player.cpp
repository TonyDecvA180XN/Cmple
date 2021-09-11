int x, y;

Create{
    x = 0
    y = 0
}

Destroy{

}

Update{
    if(keyboard_is_pressed(KEY_UP))
        y += 5;
    if(keyboard_is_pressed(KEY_DOWN))
        y -= 5;
}

Draw{
    draw_sprite(sprite_ball, x, y);
}
