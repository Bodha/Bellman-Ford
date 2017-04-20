/*define a structure to save the node locates in each edge
 *dist stands for distance to begin point
 *pres stands for predecessor of current node
 */
typedef struct
{
	int dist, pres;
} NodeType;


/*define a structure to save the edge of undirected graph
 *pt1 and pt2 are the end point of edge
 */
typedef struct 
{
    int pt1, pt2;
} EdgeType;


/* Data structure for an linked list of ints */
struct listType 
{
    int i;
    struct listType *next;
};


/*This function implements Bellman-Ford algorithm 
 *origin is the begin point of path
 *nVerts stands for the total amount of vertex in graph
 *nEdges stands for the total amount of edges in graph
 *nodes is a pointer who points to NodeType
 *edges is a pointer who points to EdgeType
*/
void BellmanFord(int origin, int nVerts, int nEdges, NodeType *nodes, EdgeType *edges) 
{
	int i, j;
	//n vertex have n edges in one route at most
	for (i = 0; i < nVerts; ++i)
	{
		//initiating every nodes
		nodes[i].dist = nVerts;
		nodes[i].pres = -1;	//default negative value to represent no predecessor
	}
	//the distance to origin point itself is zero
	nodes[origin].dist = 0;
	nodes[origin].pres = -2;

	for (i = 0; i < nVerts - 1; ++i)
		for (j = 0; j < nEdges; ++j)
		{
			//relaxing precess of Bellman-Ford algorithm
			if (nodes[edges[j].pt1].dist + 1 < nodes[edges[j].pt2].dist)
			{
				nodes[edges[j].pt2].dist = nodes[edges[j].pt1].dist + 1;
				nodes[edges[j].pt2].pres = edges[j].pt1;	//record its predecessor
			}
			if (nodes[edges[j].pt2].dist + 1 < nodes[edges[j].pt1].dist)
			{
				nodes[edges[j].pt1].dist = nodes[edges[j].pt2].dist + 1;
				nodes[edges[j].pt1].pres = edges[j].pt2;
			}
		}
}

/*This function generate the shortest path if it exists
*tempflag is a variable to represent if the origin and end have been exchanged
*if not, it should be less than zero (should be -1)
*/
void GenPath (NodeType *nodes, int nVerts, int origin, int end, int tempflag)
{
	//if shortest path exists, finding each vertex backward in path from the end point
	int i = end;
	int j = 1; //j stands for the amount of vertex in the shortest path
	int *path = NULL;
	path = (int *)malloc(sizeof(int)*nVerts);
	if ( path==NULL)
	{
		printf("Error: malloc() returned NULL.\n");fflush(stdout);
	}
	else
	{
		path[0] = end;
		while(nodes[i].pres!=-1)
		{
			path[j]=nodes[i].pres;
			//finding out the origin
			if(path[j]==origin)
			{
				//if origin and end points never exchanges each other
				//print the path reversely in order to acquire the correct order
				//because they are reversed order when stored
				if(tempflag<0)
				{
					for(i=j;i>0;i--)
					printf("%d-",path[i]);
					printf("%d\n",path[0]);fflush(stdout);
				}
				else
				{
					for(i=0;i<j;i++)
					printf("%d-",path[i]);
					printf("%d\n",path[j]);fflush(stdout);
				}
				//release this area in memory
				free(path);
				path=NULL;
					
				return;
			}
			j++;
			i=nodes[i].pres;
		}
		//if not path between this two vertex, print error message
		printf("Error: There is no path between %d and %d\n",origin,end); fflush(stdout);
	}
	free(path);
	path=NULL;
	return;
}
