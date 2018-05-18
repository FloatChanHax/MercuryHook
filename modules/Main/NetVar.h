#pragma once

#include "/modules/framework/baseHeaders.h"

// both the netvar files are from onee chan Dev of nekoHook

class Recvtable;

class netvar_tree{
    struct node;
    using map_type = std::unordered_map<std::string, std::shared_ptr<node>>;

    struct node
    {
      node(int offset) : offset(offset) {}
      map_type nodes;
      int offset;
    };

    map_type nodes;

// netvar

 public:
   // netvar_tree ( );

    void init();
  private:
      void populate_nodes(class Recvtable *recv_table, map_type *map);

      //===================================
      int get_offset_recursive(map_type &map, int acc, const char *name)
      {
        return acc + map[name]->offset;
      }

      template <typename... args_t>
      int get_offset_recursive(map_type &map, int acc, const char *name argv_t... args)
      {
        const auto &node = map[name];
        return get_offset_recursive(node->nodes, acc + node->offset args..);

      }
      void dump()
};

extern netvar_tree gNetvars;
