class Player
{
    private:
    Ray hit_ray;
    Ray feet;



    public:
    Camera camera  = { 0 };
    Player(Vector3 position = (Vector3){ 32.0f, 34.0f, 32.0f }, Vector3 target = (Vector3){ 0.0f, 34.0f, 32.0f }, float fov = 45.0f);
    Player(Vector3 position, float fov);
    ~Player();

    void update();
    Ray get_Hit_Ray();

};