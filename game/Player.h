enum class Character {NOT_SELECTED, Alice, Bob, Carol, Dave};

class Player {
    private:
        int id;
        Character character;
        float speed;
        int insecurity;
        int awareness;
        bool seeAliceLocation;

    public:
        Player(int id);

        void setCharacter(Character charChoice);
        void setInsesurityLevel(int num);
        void setAwarenessLevel(int num);
        void setSeeAliceLocation(bool visible);

        int getPlayerId();
        Character getCharacter();
        int getInsesurityLevel();
        int getAwarenessLevel();
        bool getSeeAliceLocation();
};