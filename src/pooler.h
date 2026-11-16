//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#ifndef POOLER_H
#define POOLER_H

#include <memory>
#include <list>
#include <vector>
#include <deque>

#include "enemy.h"

// Implement the following methods:
// Clear()
// SpawnEnemy()
// DespawnEnemy()
// GetActiveEnemies()

class Pooler {
   public:
    Pooler(size_t minimumPoolSize);
    size_t PoolSize() const;

    // clear the enemy pool
    void Clear();

    // spawns an enemy. Takes in x/y coordinates via a  
    Enemy* SpawnEnemy(Vector2D position);

    // removes a given enemy from the game, and adds them to the pool
    void DespawnEnemy(Enemy* enemy);

    // returns the enemies list (read only)
    const std::vector<Enemy*>& GetActiveEnemies() const;


   private:
    std::vector<Enemy*> active_enemies;
    std::vector<Enemy*> enemy_pool;
    std::deque<Enemy> enemy_storage;
    size_t minimumPoolSize;

    // Creates an enemy, adds it to active_enemy. draws from enemy_pool if possible
    Enemy* CreateEnemy();
    
    // Resets pool back to base state. clears previous pool and reinitializes with new one 
    void Reset();
};

#endif  // POOLER_H