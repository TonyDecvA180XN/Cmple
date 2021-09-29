int Time;
player my_player;

Create{
    my_player& = create_object_player();
    player nnn;
    Time = 0;
}

Destroy{

}

Update{
    Time += 1;
    if(rand()%10 == 0)
        my_player->x += 10;
}

Draw3D{

}

Draw2D{
    // draw_text(32, 48, to_string(Time));
}
