class controll {
public:
	int Time;
	player_typename my_player;
	
	void Create() {
	    player_container[my_player] = create_object_player();
	    player_typename nnn;
	    player_container[nnn].data++;
	    Time = 0;
	}
	
	void Destroy() {
	
	}
	
	void Update() {
	    nnn.data++;
	    Time += 1;
	    if(random_int(0,10) == 0)
	        player_container[my_player].x += 10;
	}
	
	void Draw() {
	    draw_text(to_string(Time), 32, 32);
	}
	
}
