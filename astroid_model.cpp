

class astroid_model{

	private:

		struct spaceObject{
			float x;
			float y;
			float dx;
			float dy;
			int size;
			float angle;
		}

		std::vector<spaceObject> asteroids;
		std::vector<spaceObject> bullets;
		spaceObject player;
		bool dead = false;
		int nScore = 0;

		std::vector<pair<float, float>> ship_model;
		std::vector<pair<float, float>> vec_astroid_model;


	public:

		spaceObject getPlayer(){
			return player;
		}

		int getScore(){
			return nScore;
		}

		std::vector<pair<float, float>> getShipModel(){
			return ship_model;
		}

		std::vector<pair<float, float>> getAsteroidModel(){
			return vec_astroid_model;
		}

		std::vector<spaceObject> getBullets(){
			return bullets;
		}

		std::vector<spaceObject> getAsteroids(){
			return asteroids;
		}

		bool OnUserCreate(){
			ship_model = {
				{0.0f, -4.0f},
				{-2.5f, 2.5f},
				{2.5f, 2.5f}
			};

			int points = 30;
			for (int i = 0; i<points; i++){
				float standard_dev = (float) rand() / (float) RAND_MAX * 0.3f + 0.9f;
				vec_astroid_model.push_back(make_pair(standard_dev*sinf(((float)i/(float)points) * 6.28318f),
					standard_dev * cosf(((float)i / (float)points) * 6.28318f)));

			}
			ResetGame();
			return true;
		}

		void resetGame(){
			player.x = ScreenWidth() / 2.0f;
			player.y = ScreenWidth() / 2.0f;
			player.dx = 0.0f;
			player.dy = 0.0f;
			player.angle = 0.0f;
			player.lives = 3;

			bullets.clear()
			asteroids.clear();

			asteroids.push_back({(int)16, 20.0f, 20.0f, 8.0f, -6.0f, 0.0f});
			asteroids.push_back({(int)16, 100.0f, 20.0f, -5.0f, 3.0f, 0.0f});

			dead = false;
			score = 0;
		}

		// FIX
		void wrapCords(float x, float y, float &out_x, float &out_y){
			out_x = x;
			out_y = y;
			if(x < 0.0)
				out_x = x + (float)ScreenWidth();
			if(x > (float)ScreenWidth())
				out_x = x - (float)ScreenWidth();
			if(y < 0.0)
				out_y = y + (float)ScreenWidth();
			if(y > (float)ScreenWidth())
				out_y = y - (float)ScreenWidth();
		}

		// wills main part
		void update_movement(float fElapsedTime){
			if(m_keys[VK_LEFT].bHeld){// left key held
				player.angle -= 6.0 * fElapsedTime;
			}
			if(m_keys[VK_RIGHT].bHeld){// right key held
				player.angle += 6.0 * fElapsedTime;
			}

			if(m_keys[VK_UP].bHeld){// thrust
				player.dx += sin(player.angle) * 20.0f * fElapsedTime;
				player.dy += -cos(player.angle) * 20.0f * fElapsedTime;
			}

			player.x += player.dx * fElapsedTime;
			player.y += player.dy * fElapsedTime;

			wrapCords(player.x, player.y, player.x, player.y);

			if(m_keys[VK_SPACE].bReleased){
				bullets.push_back({0, player.x, player.y, 50.0f * sinf(player.angle), -50.0f * cosf(player.angle), 100.0f});
			}

			for (auto &a : asteroids){
				a.x += a.dx * fElapsedTime;
				a.y += a.dy * fElapsedTime;
				a.angle += 0.5f * fElapsedTime;
				wrapCords(a.x, a.y, a.x, a.y);
			}

			for (auto &b : bullets){
				b.x += b.dx * fElapsedTime;
				b.y += b.dy * fElapsedTime;
				wrapCords(b.x, b.y, b.x, b.y);
			}

			std::vector<spaceObject>::iterator it;
			for(it = bullets.begin(); it != bullets.end();){
				if(it->x < 1 || it->y < 1 || it->x > ScreenWidth() || it->y > ScreenHeight()){
					it = bullets.erase(it);
				}else{
					it++;
				}
			}

		}

		bool OnUserUpdate(float fElapsedTime){
			if(dead){
				resetGame();
			}

			update_movement(fElapsedTime); // will

			// check for collision, connor

			// update view, neil

		}

}