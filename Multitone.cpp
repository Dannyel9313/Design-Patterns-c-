#include <iostream>
#include <map>
#include <memory>

enum PlaylistName
{
    eJazz,
    ePop,
    eHipHop,
    eNumObjects
};


template<typename T, typename Key = int>
class Multiton
{
public:
    static void Destroy()
    {
        instances.clear();
    }

    static std::shared_ptr<T> GetInstance(const Key& key)
    {
        auto it = instances.find(key);
        if(it != instances.end())
            return it->second;
        auto instance = std::make_shared<T>();
        if(instance)
            instances[key] = instance;
        return instances[key];
    }


protected:
    Multiton(const Key& key){};
    virtual ~Multiton() = default;
private:
    Multiton(const Multiton&) = delete;
    Multiton& operator=(const Multiton&) = delete;

    static std::map<Key, std::shared_ptr<T>> instances;
};

template<typename T, typename Key>
std::map<Key, std::shared_ptr<T>> Multiton<T,Key>::instances;

class Playlist
{
public:
    Playlist(){ std::cout << "Play list with id - " << ++playlistId << " has been created!!!\n";};
private:
    static int playlistId;
};

int Playlist::playlistId = 0;

int main(int argc, char *argv[])
{
    auto HipHopPlaylist = Multiton<Playlist,PlaylistName>::GetInstance(PlaylistName::eHipHop);
    auto HipHopPlaylistSecond = Multiton<Playlist,PlaylistName>::GetInstance(PlaylistName::eHipHop);
    auto JazzPlaylist = Multiton<Playlist,PlaylistName>::GetInstance(PlaylistName::eJazz);
    auto JazzPlaylistSecond = Multiton<Playlist,PlaylistName>::GetInstance(PlaylistName::eJazz);
    auto PopPlaylist = Multiton<Playlist, PlaylistName>::GetInstance(PlaylistName::ePop);

    std::cout << "Object addresses:" << std::endl
              << HipHopPlaylist      << std::endl
              << HipHopPlaylistSecond<< std::endl
              << JazzPlaylist        << std::endl
              << JazzPlaylistSecond  << std::endl
              << PopPlaylist         << std::endl;

    return 0;
}
