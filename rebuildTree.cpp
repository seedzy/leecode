输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。

 

例如，给出

前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]
返回如下的二叉树：

    3
   / \
  9  20
    /  \
   15   7

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof



class Solution7 {
public:
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		unordered_map<int, int> map;
		for (int i = 0; i < inorder.size(); i++) {
			map.insert({ inorder[i], i });
		}
		return buildTreeNode(preorder, inorder, 0, 0, inorder.size() - 1, map);

	}

	TreeNode* buildTreeNode(vector<int>& preorder, vector<int>& inorder, int preRoot, int inBegin, int inEnd,unordered_map<int,int>& map) {
		//如果下标越界，则左/右子树为空
		if (inBegin > inEnd)
			return nullptr;

		//使用根节点建立子树
		TreeNode* tree = new TreeNode(preorder[preRoot]);

		//若中序遍历数组存在前序中包含的根节点，则递归建立其左右子树
		if (map.count(preorder[preRoot])) {
			//建立左子节点:
			//		1.前序遍历数组中根节点的下一个元素，一定是其左子节点，因此使用 preRoot+1 作为左子树根节点。
			//		2.由于中序遍历数组中，树根节点元素左右两侧必定为该树的左右子树节点，因此以中序数组中的根节点为界
			//		   划分左右子树元素 inBegin, map[preRoot - 1]					   
			tree->left = buildTreeNode(preorder, inorder, preRoot + 1, inBegin, map[preorder[preRoot]] - 1, map);
			//建立右子节点:
			//		1.前序遍历数组中从左至右除去根节点和根节点的左子树元素后的下一个元素，一定是其右子节点，
			//		   因此使用 preRoot + 1 + (map[preRoot] - inBegin) 作为右子树根节点。
			//		2.由于中序遍历数组中，树根节点元素左右两侧必定为该树的左右子树节点，因此以中序数组中的根节点为界
			//		   划分左右子树元素 map[preorder[preRoot + 1]], inEnd			
			tree->right = buildTreeNode(preorder, inorder, preRoot + 1 + (map[preorder[preRoot]] - inBegin), map[preorder[preRoot]] + 1, inEnd, map);
		}
		return tree;
	}
};