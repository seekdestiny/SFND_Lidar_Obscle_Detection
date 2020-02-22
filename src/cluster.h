#ifndef CLUSTER_H_
#define CLUSTER_H_

#include <chrono>
#include <string>


inline void clusterHelper(std::vector<int>& cluster, std::vector<bool>& processed, const std::vector<std::vector<float>>& points, int indice,
                   KdTree* tree, float distanceTol) {
   processed[indice] = true;
   cluster.push_back(indice);
     
   std::vector<int> ids = tree->search(points[indice], distanceTol);
   for (int id : ids) {
    if (!processed[id]) {
      clusterHelper(cluster, processed, points, id, tree, distanceTol);
    }
   }
}

inline std::vector<std::vector<int>> euclideanCluster(const std::vector<std::vector<float>>& points, KdTree* tree, float distanceTol)
{

	// TODO: Fill out this function to return list of indices for each cluster

	std::vector<std::vector<int>> clusters;
  std::vector<bool> processed(points.size(), false);

  int i = 0;
  while (i < points.size()) {
    if (processed[i]) {
      i++;
      continue;
    }

    std::vector<int> cluster;
    clusterHelper(cluster, processed, points, i, tree, distanceTol);
    clusters.push_back(cluster);
    i++;
  }

	return clusters;
}

#endif
