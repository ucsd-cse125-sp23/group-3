enum class Character {Alice, Bob, Carol, Dave};

class Player {
    private:
        int id;
        bool blind; // Alice: true; others: false
        float speed;
        int insecurity;
        int awareness;
        bool seeAliceLocation;

    public:
        Player(int id);

        void setPlayerId(int id);
        void setCharacter(Character charChoice);
        void setInsesurityLevel(int num);
        void setAwarenessLevel(int num);
        void setSeeAliceLocation(bool visible);

        void getPlayerId();
        Character getCharacter();
        int getInsesurityLevel();
        int getAwarenessLevel();
        bool getSeeAliceLocation();
};