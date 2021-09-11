class player {
public:
	int x, y;
	
	void Create() {
	    x = 0
	    y = 0
	}
	
	void Destroy() {
	
	}
	
	void Update() {
	    if(keyboard_is_pressed(KEY_UP))
	        y += 5;
	    if(keyboard_is_pressed(KEY_DOWN))
	        y -= 5;
	}
	
	void Draw() {
	    draw_sprite(sprite_ball, x, y);
	}
	
}
