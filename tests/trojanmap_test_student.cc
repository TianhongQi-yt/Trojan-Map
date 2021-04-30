#include <map>
#include <vector>

#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

// Test Autocomplete function
TEST(TrojanMapTest, Autocomplete) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test the simple case
  auto names = m.Autocomplete("Sai");
  std::vector<std::string> gt1 = {"Saint James Park", "Saint Agnes Elementary School", "Saint Marks Lutheran Church"}; // groundtruth for "Sai"
  EXPECT_EQ(names, gt1);
  // Test the upper case
  names = m.Autocomplete("SAI");
  std::vector<std::string> gt2 = {"Saint James Park", "Saint Agnes Elementary School", "Saint Marks Lutheran Church"}; // groundtruth for "SAI"
  EXPECT_EQ(names, gt2);
  // Test the lower and upper case 
  names = m.Autocomplete("sAi"); 
  std::vector<std::string> gt3 = {"Saint James Park", "Saint Agnes Elementary School", "Saint Marks Lutheran Church"}; // groundtruth for "sAi"
  EXPECT_EQ(names, gt3);
  // Test the empty input case 
  names = m.Autocomplete(""); 
  std::vector<std::string> gt4 = {}; // groundtruth for ""
  EXPECT_EQ(names, gt4);
  // Test the no found case
  names = m.Autocomplete("asdf"); 
  std::vector<std::string> gt5 = {}; // groundtruth for "asdf"
  EXPECT_EQ(names, gt5);
}

// Test FindPosition function
TEST(TrojanMapTest, FindPosition) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test University Park
  auto position = m.GetPosition("University Park");
  std::pair<double, double> gt1(34.027449, -118.2839493); // groundtruth for "University Park"
  EXPECT_EQ(position, gt1);
  // Test the empty case
  position = m.GetPosition("");
  std::pair<double, double> gt2(-1, -1);
  EXPECT_EQ(position, gt2);
  // Test no found case
  position = m.GetPosition("asdf");
  std::pair<double, double> gt3(-1, -1);
  EXPECT_EQ(position, gt3);
}

// Test CalculateShortestPath_Dijkstra function
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Ralphs to Target
  auto path = m.CalculateShortestPath_Dijkstra("Ralphs", "Target");
  std::vector<std::string> gt{
      "2578244375", "5559640911", "6787470571", "6808093910", "6808093913", "6808093919", "6816831441",
      "6813405269", "6816193784", "6389467806", "6816193783", "123178876", "2613117895", "122719259",
      "6807243574", "6807243576", "213332111", "441895337", "441895335", "122719255", "2613117893",
      "6813405231", "122719216", "6813405232", "4015372486" ,"7071032399" ,"4015372485","6813379479",
      "5237417650"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Target
  path = m.CalculateShortestPath_Dijkstra("Target", "Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// No path case
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra_noPath) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Dijkstra("Moreton Fig", "Mercado la Paloma");
  std::vector<std::string> gt;  // expect no path
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  // Reverse the input
  path = m.CalculateShortestPath_Dijkstra("Mercado la Paloma", "Moreton Fig");
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Invalid input case
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra_invalidInput) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Dijkstra("asd", "qwe");
  std::vector<std::string> gt;  // expect no path
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test CalculateShortestPath_Bellman_Ford function
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Ralphs to Target
  auto path = m.CalculateShortestPath_Bellman_Ford("Ralphs", "Target");
  std::vector<std::string> gt{
      "2578244375", "5559640911", "6787470571", "6808093910", "6808093913", "6808093919", "6816831441",
      "6813405269", "6816193784", "6389467806", "6816193783", "123178876", "2613117895", "122719259",
      "6807243574", "6807243576", "213332111", "441895337", "441895335", "122719255", "2613117893",
      "6813405231", "122719216", "6813405232", "4015372486" ,"7071032399" ,"4015372485","6813379479",
      "5237417650"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Target
  path = m.CalculateShortestPath_Bellman_Ford("Target", "Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// No path case
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford_noPath) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Bellman_Ford("Moreton Fig", "Mercado la Paloma");
  std::vector<std::string> gt;  // expect no path
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  // Reverse the input
  path = m.CalculateShortestPath_Bellman_Ford("Mercado la Paloma", "Moreton Fig");
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Invalid input case
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford_invalidInput) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Bellman_Ford("asd", "qwe");
  std::vector<std::string> gt;  // expect no path
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test TSP function
TEST(TrojanMapTest, TSP) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"4015405541", "6813513563", "122719213", "6815190433", "122817161"}; // Input location ids 
  auto result = m.TravellingTrojan_2opt(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"4015405541", "6815190433", "122719213", "6813513563", "122817161", "4015405541"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapTest, TSP2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"123120189", "4011837229", "4011837224", "2514542032", "2514541020", "4015477529", "214470792", "63068532", "6807909279"}; // Input location ids 
  auto result = m.TravellingTrojan_2opt(input);
  std::cout << "My path length: " <<result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"123120189", "4011837224", "4011837229", "2514542032", "2514541020", "6807909279", "63068532", "214470792", "4015477529", "123120189"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  
  EXPECT_EQ(flag, true);
}

// Invalid input case
TEST(TrojanMapTest, TSP_invalid) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input;  // null input
  auto result = m.TravellingTrojan(input);
  EXPECT_EQ(result.first, 0);
  input = {"7424270441"};  // only one element input
  result = m.TravellingTrojan(input);
  EXPECT_EQ(result.first, 0);
}

// Test cycle detection function
TEST(TrojanMapTest, CycleDetection) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test case 1
  std::vector<double> square1 = {-118.2899, -118.26399, 34.03199, 34.01099};
  bool result1 = m.CycleDetection(square1);
  EXPECT_EQ(result1, true);

  // Test case 2
  std::vector<double> square2 = {-118.290920, -118.282912, 34.02236, 34.019676};
  bool result2 = m.CycleDetection(square2);
  EXPECT_EQ(result2, false);

  // Test case 2
  std::vector<double> square3 = {-118.264, -118.264, 34.032, 34.032};
  bool result3 = m.CycleDetection(square3);
  EXPECT_EQ(result3, false);
}

// Test Topological Sort function
// The cycle case
TEST(TrojanMapTest, TopologicalSort_cycle) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"Cardinal Gardens", "Coffee Bean1", "CVS"};
  std::vector<std::vector<std::string>> dependencies = {{"Cardinal Gardens","Coffee Bean1"}, {"Cardinal Gardens","CVS"}, {"Coffee Bean1","CVS"}, {"Coffee Bean1","Cardinal Gardens"}, {"CVS","Cardinal Gardens"}, {"CVS","Coffee Bean1"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt; // empty path
  EXPECT_EQ(result, gt);
}

// The no_connection case
TEST(TrojanMapTest, TopologicalSort_noConection) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"Cardinal Gardens", "Coffee Bean1", "CVS", "Kentucky Fried Chicken", "Target"};
  std::vector<std::vector<std::string>> dependencies = {{"Cardinal Gardens","Coffee Bean1"}, {"Cardinal Gardens","CVS"}, {"Coffee Bean1","CVS"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt; // empty path
  EXPECT_EQ(result, gt);
}

TEST(TrojanMapTest, TopologicalSort) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"Cardinal Gardens", "Coffee Bean1", "CVS", "Kentucky Fried Chicken", "Target"};
  std::vector<std::vector<std::string>> dependencies = {{"Cardinal Gardens","Coffee Bean1"}, {"Cardinal Gardens","CVS"}, {"Coffee Bean1","CVS"}, {"Kentucky Fried Chicken","Cardinal Gardens"}, 
                                                        {"Kentucky Fried Chicken","Coffee Bean1"}, {"Kentucky Fried Chicken","CVS"}, {"Target","CVS"}, {"Target","Cardinal Gardens"}, 
                                                        {"Target","Coffee Bean1"}, {"Target","Kentucky Fried Chicken"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt = {"Target", "Kentucky Fried Chicken", "Cardinal Gardens", "Coffee Bean1", "CVS"};
  EXPECT_EQ(result, gt);
}





