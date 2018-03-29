/**************************************************************
 * File: TreeNode.hpp
 *
 * Description: Node class for the custom tree implementation.
 *              The node represents a path in the maze. Holds
 *              a visit counter to track when the path can be
 *              closed off. 
 * 
 * @author Group 1
 **************************************************************/

// TODO: This will not work if there are loops in the maze
#include "MovementControl.hpp"

class TreeNode 
{
    public:
        /**
         * Construct a new Tree Node object
         * 
         * @param parent Parent node for the new node (NULL for root)
         */
        TreeNode(TreeNode* parent);

        /**
         * Since the node represents a junction, this function adds
         * a connecting path along with the direction that the robot
         * can go to start along that path.
         * 
         * @param direction Direction of the path from the robot 
         * @param path Next node in the tree representing the path
         */
        void addPath(Direction direction, TreeNode* path);

        /**
         * Get the Parent object
         * 
         * @return TreeNode* Parent node, NULL if root 
         */
        TreeNode* getParent();

    private:
        /* Store the parent of the node for traversal */
        TreeNode* parent;

        /* Store all the possible paths for the junction */
        TreeNode* paths[MAX_DIRECTION];
}