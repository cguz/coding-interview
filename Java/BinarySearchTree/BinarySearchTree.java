package BinarySearchTree;
/**
 * @author cguzman@cguz-org
 * 
 * How to use the Binary Search Tree structure to save the elements of a normal Tree (size M)
 * to calculate the node that is more repeated in the Tree.
 * 
 * Let v be a node and M be the set of nodes in the Tree, 
 * such as M can have repeated values of key(v). 
 * In addition, we assume N is the set of no repeated key(v) values.
 * 
 * Space complexity: BinarySearchTree 
 * Time complexity: M * O(log(N))
 *
 * @param <Node>
 */
public class BinarySearchTree<Node>{
	

	/** root node of the BST **/
	private Node root; 

	/** Node that is more repeated in the BST **/
	private Node nodeMoreRepeated;

	/**
	 * Constructor
	 * @param value initial root Node
	 */
	public BinarySearchTree(double value){
		root = new Node(value);
		nodeMoreRepeated = root;
		copyElements(root);
	}

	/**
	 * insert a data in the BST
	 * @param data
	 */
	public void insert(double data) {
		Node node = new Node(data);

		if (root == null) {
			root = node;
			return;
		}

		insert(root, node);
	}

	/**
	 * insert a node in the BST 
	 * this function saves the node that is more repeated in the BST
	 *  
	 * @param currentRoot current root node
	 * @param node Node to insert from a given root node
	 */
	private void insert(Node currentRoot, Node node) {
		if (currentRoot.data == node.data) {
			currentRoot.count++;
			if (currentRoot.count > nodeMoreRepeated.count) {
				nodeMoreRepeated = currentRoot;
			}
			return;
		} else {
			if (currentRoot.data < node.data) {
				if (currentRoot.left == null) {
					currentRoot.left = node;
					return;
				} else {
					insert(currentRoot.left, node);
				}
			} else {
				if (currentRoot.right == null) {
					currentRoot.right = node;
					return;
				} else {
					insert(currentRoot.right, node);
				}
			}
		}
	}

	/**
	 * copy the elements of a given Tree to the BST
	 * 
	 * @param rootTree root node of the tree
	 */
	public void copyElements(Node rootTree) {
		traversal(rootTree);
	}

	/**
	 * post order traversal of the tree
	 * @param node
	 */
	private void traversal(Node node) {
		if (node == null)
			return;
		traversal(node.left);
		traversal(node.right);
		insert(node.data);
	}

	/**
	 * retrieve the maximum data of the BST
	 * @return
	 */
	private double getMoreRepeatedNode() {
		return nodeMoreRepeated.data;
	}

	/**
	 * Find the most repeated node in the tree
	 * 
	 * @param root root node of the tree
	 * @return double value of the most repeated node
	 */
	public double findRepeatedNode(Node root) {
		
		BinarySearchTree<Node> bst = new BinarySearchTree<Node>(root.data);
		return bst.getMoreRepeatedNode();
		
	}
	

	
	/**
	 * Node of the BST
	 * 
	 * @author cguzman@cguz.org
	 * 
	 */
	public class Node{
		
		/** value of the data in the Node **/
		double data;
		
		/**  variable to save repeated nodes or data **/
		int count;

		/** left node of the BST, values less than the root **/
		Node left;
		
		/** right node of the BST, values higher or equals than the root **/
		Node right;

		/**
		 * Constructor
		 * @param data value of the Node
		 */
		public Node(double data){
			this.data = data;
			count = 1;
		}
	}
}
