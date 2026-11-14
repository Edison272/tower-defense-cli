//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#ifndef POOLER_H
#define POOLER_H

#include <memory>
#include <list>
#include <vector>

#include "enemy.h"

// Implement the following methods:
// Clear()
// SpawnEnemy()
// DespawnEnemy()
// GetActiveEnemies()

class Pooler {
   public:
    Pooler(size_t minimumPoolSize);
    size_t PoolSize();

    // clear the enemy pool
    void Clear();

    // spawns an enemy. Takes in x/y coordinates via a  
    Enemy* SpawnEnemy(std::list<int> position);

    // removes a given enemy from the game, and adds them to the pool
    void DespawnEnemy(Enemy* enemy);

    // returns the enemies list
    std::vector<Enemy*> GetActiveEnemies();

   private:
    std::vector<Enemy*> active_enemies;
    std::vector<Enemy*> enemy_pool;
    size_t minimumPoolSize;

    Enemy* CreateEnemy();
};

#endif  // POOLER_H