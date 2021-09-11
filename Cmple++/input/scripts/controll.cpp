int Time;
player my_player;

Create{
    my_player = create_object_player();
    player nnn;
    nnn.data++;
    Time = 0;
}

Destroy{

}

Update{
    nnn.data++;
    Time += 1;
    if(random_int(0,10) == 0)
        my_player.x += 10;
}

Draw{
    draw_text(to_string(Time), 32, 32);
}
