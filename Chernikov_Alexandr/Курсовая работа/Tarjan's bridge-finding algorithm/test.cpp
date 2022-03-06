#include <gtest/gtest.h>
#include "graph.h"


TEST(test_create_random_graph, test_negarive_edges){
    Graph g1 = create_random_graph(-1);
    ASSERT_EQ(g1.get_number_of_edges(), 0);
}

TEST(test_create_random_graph, test_zero_edges){
    Graph g1 = create_random_graph(0);
    ASSERT_EQ(g1.get_number_of_edges(), 0);
}

TEST(test_create_random_graph, test_positive_edges){
    Graph g1 = create_random_graph(1);
    ASSERT_EQ(g1.get_number_of_edges(), 1);

    Graph g2 = create_random_graph(2);
    ASSERT_EQ(g2.get_number_of_edges(), 2);

    Graph g3 = create_random_graph(8);
    ASSERT_EQ(g3.get_number_of_edges(), 8);

    Graph g4 = create_random_graph(100);
    ASSERT_EQ(g4.get_number_of_edges(), 100);
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}