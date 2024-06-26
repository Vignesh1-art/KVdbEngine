#ifndef BTREE
#define BTREE
#include "TypeDefs.h"
#include "Page.h"
#include "Key.h"
#include "Value.h"
#include "KeyValueFactory.h"
#include <memory>
#define RECORD_MAX_SIZE 512

enum NodeType {
    ROOT_NODE = 0, INTERNAL_NODE = 1, LEAF_NODE = 2, OVERFLOW_NODE = 3
};

class BTNode {
    public:
    BTNode(std::shared_ptr<Page> page);
    BTNode(BTNode &node) {
        temporaryRecordBuffer = new char[RECORD_MAX_SIZE];
        page = node.page;
    }
    BTNode() {

    }
    ~BTNode() {
        if(!temporaryRecordBuffer) {
            delete temporaryRecordBuffer;
        }
    }
    uint16 insert(std::shared_ptr<Key> key, std::shared_ptr<Value> value);
    void remove(uint16 index);
    void split(std::shared_ptr<BTNode> splittedNode);
    void merge(std::shared_ptr<BTNode> node);
    uint16 search(std::shared_ptr<Key> key);
    uint16 searchCmp(std::shared_ptr<Key> key);
    std::shared_ptr<Key> getKey(uint16 index);
    std::shared_ptr<Value> getValue(uint16 index);
    uint16 getItemCount();
    uint64 getChildID(uint16 index);
    uint16 searchChild(uint64 childID);
    uint64 getID();
    void setChildID(uint16 index, uint64 id);
    NodeType getNodeType();
    void setNodeType(NodeType type);
    void swapID(std::shared_ptr<BTNode> node);
    void updateKeyValue(std::shared_ptr<Key> key, std::shared_ptr<Value> value, uint16 index);
    bool hasMinimum();
    bool isRootNode();
    private:
    std::shared_ptr<Page> page;
    char* temporaryRecordBuffer;
    KeyValueFactory kvFactory;
    uint16 serializeToTemporaryBuffer(std::shared_ptr<Key> key, std::shared_ptr<Value> value);
    NodeType mapToNodeType(PageType type);
    PageType mapToPageType(NodeType type);
};

#endif