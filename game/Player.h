enum class Character {NOT_SELECTED, Alice, Bob, Carol, Dave};

class Player {
    private:
        int id;
        Character character;
        float speed;
        int level; // insecurity for Alice, awareness for others
        bool seeAliceLocation;

    public:
        Player(int id);

        void setCharacter(Character charChoice);
        void setLevel(int num);
        void setSeeAliceLocation(bool visible);

        int getPlayerId();
        Character getCharacter();
        int getLevel();
        bool getSeeAliceLocation();
};