/**
  * author Float
  * credit to onee chan for helping
  **/
#include "/modules/Main/NetVar.h"
#include "/modules/framework/SDK.h"

// Call populate_nodes - client->GetAllClasses()

void netvar_tree:init()
{
    const auto *client_class = gInts.Client->GetAllClasses();
    while(client_class != nullptr)
    {
        const auto class_info = std::make_shared<node>(0);
        auto *recv_table = client_class->Table;
        populate_nodes(recv_table, &class_info->nodes);
        nodes.emplace(recv_table->GetName(), class_info);

        client_class = client_class->pNextClass;
    }
}

//=============================
void netvar_tree::populate_nodes(recvTable *recv_table, map_type *map){
    for(auto i = 0; i < recv_table->GetNumProps(); i++){
        const auto *prop = recv_table->GetProp(i);
        const auto prop_info = std::make_shared<node>(prop->GetOffset());

          if(!prop->GetType() == NULL)
          return NULL;

          if(prop->GetType() == DPT_DataTable)
              populate_nodes(prop->GetDataTable(), &prop_info->nodes);

            map->emplace(prop->GetName(), prop_info);
    }
}

netvar_tree gNetvars;
