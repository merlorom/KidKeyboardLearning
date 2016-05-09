namespace KeyLabyrinth {

class Tile {
public:
    enum WallDir {
      Down = 1,
      Left = 2,
      Up = 4,
      Right = 8
    };

public:
    Tile();
    virtual ~Tile();

    char key() const;
    void set_key( char key );

    int walls() const;
    void set_wall( WallDir dir, bool set );
    bool has_wall( WallDir dir ) const;

private:
    char key_;
    int walls_;
};

inline char Tile::key() const {
    return key_;
}

inline void Tile::set_key( char key ) {
    key_ = key;
}

inline int Tile::walls() const {
    return walls_;
}

inline bool Tile::has_wall( WallDir dir ) const {
    return walls_ & dir;
}

}
