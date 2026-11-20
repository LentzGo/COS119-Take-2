#pragma once
#include <string>
#include "CollectionManager.h"

class StorageService {
private:
    std::string filePath;

public:
    StorageService(const std::string& filePath);

    bool saveCollection(const CollectionManager& manager) const;
    bool loadCollection(CollectionManager& manager, int& loadedCount) const;
    std::string getFilePath() const;
};

