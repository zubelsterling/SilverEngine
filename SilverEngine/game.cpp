#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float player_p, player_dp;
float arena_half_size_x = 85, arena_half_size_y = 45;


internal void 
simulate_game(Input* input, float dt) {
	clear_screen(0x000000);
	draw_rect(0, 0, arena_half_size_x, arena_half_size_y, 0xffaa33);

	float player_ddp = 0.f;
	//if (is_down(BUTTON_SPACE)) speed *= 10;
	if (is_down(BUTTON_UP)) player_ddp += 2000;
	if (is_down(BUTTON_DOWN)) player_ddp -= 2000;

	player_ddp -= player_dp * 10.f;

	player_p = player_p + player_dp * dt + player_ddp * dt * dt * .5f;
	player_dp = player_dp + player_ddp * dt; 


	draw_rect(0, 0, 1, 1, 0xffffff);

	draw_rect(80, player_p, 2.5, 12, 0xff0000);
	draw_rect(-80, 0, 2.5, 12, 0xff0000);
	//draw_rect(player_pos_x, player_pos_y, 5, 5, 0xffffff);
}