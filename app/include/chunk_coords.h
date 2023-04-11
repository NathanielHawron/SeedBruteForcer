#pragma once

#include <fstream>
#include <filesystem>
#include <vector>

struct ChunkCoords{
    int x, y;
    static void getCoordsFromFile(std::filesystem::path path, std::vector<ChunkCoords> &res){
        std::fstream file = std::fstream(path);

        int x, y;
        while(file >> x && file >> y){
            res.push_back({x,y});
        }
    }
};