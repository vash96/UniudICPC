
vector<Player> comparator(vector<Player> players) {
    sort(players.begin(), players.end(), [](const Player& fst, const Player& snd) {
        if(fst.score != snd.score)
            return fst.score > snd.score;
        return fst.name < snd.name;
    });
    
    return players;
}

