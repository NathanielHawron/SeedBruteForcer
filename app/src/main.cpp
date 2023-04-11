#include <iostream>
#include <filesystem>
#include <vector>

#include "rand.h"
#include "chunk_coords.h"

#define PATH_APPEND_COPY(pathSrc, toAppend) std::filesystem::path(pathSrc).append(toAppend)

int main(){
    const std::filesystem::path coordsPath = std::filesystem::current_path().append("coords");
    std::vector<ChunkCoords> slimeChunks;
    ChunkCoords::getCoordsFromFile(PATH_APPEND_COPY(coordsPath,"slimeChunks.txt"),slimeChunks);
    
}