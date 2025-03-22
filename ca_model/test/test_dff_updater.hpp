#include <gtest/gtest.h>
#include <memory>
#include "../src/dff_updater.hpp"
#include "../src/dff_base.hpp"

// Test fixture for DFFUpdater
class DFFUpdaterTest : public ::testing::Test {
protected:
	std::shared_ptr<DffBase<int>> dff1;
	std::shared_ptr<DffBase<int>> dff2;
	std::shared_ptr<DffBase<int>> dff3;
	DFFUpdater<int> updater;

	void SetUp() override {
		dff1 = std::make_shared<DffBase<int>>(10);
		dff2 = std::make_shared<DffBase<int>>(20);
		dff3 = std::make_shared<DffBase<int>>(30);
	}
};

// Test default constructor
TEST_F(DFFUpdaterTest, DefaultConstructor) {
	EXPECT_EQ(updater.get_dff_count(), 0);
}

// Test registering DFFs
TEST_F(DFFUpdaterTest, RegisterDff) {
	updater.register_dff(dff1);
	EXPECT_EQ(updater.get_dff_count(), 1);
	
	updater.register_dff(dff2);
	updater.register_dff(dff3);
	EXPECT_EQ(updater.get_dff_count(), 3);
}

// Test global reset functionality
TEST_F(DFFUpdaterTest, GlobalReset) {
	updater.register_dff(dff1);
	updater.register_dff(dff2);
	
	// Set values
	dff1->set(100);
	dff2->set(200);
	dff1->clock();
	dff2->clock();
	
	EXPECT_EQ(dff1->get(), 100);
	EXPECT_EQ(dff2->get(), 200);
	
	// Apply global reset
	updater.global_reset(true);

	EXPECT_EQ(dff1->get(), 0);
	EXPECT_EQ(dff2->get(), 0);
	EXPECT_FALSE(dff1->rst_n);
	EXPECT_FALSE(dff2->rst_n);
	
	// Deactivate reset
	updater.global_reset(false);
	EXPECT_TRUE(dff1->rst_n);
	EXPECT_TRUE(dff2->rst_n);
}

// Test global clock functionality
TEST_F(DFFUpdaterTest, GlobalClock) {
	updater.register_dff(dff1);
	updater.register_dff(dff2);
	
	// Set values but don't clock individually
	dff1->set(100);
	dff2->set(200);
	
	// Values shouldn't have changed yet
	EXPECT_EQ(dff1->get(), 10);
	EXPECT_EQ(dff2->get(), 20);
	
	// Apply global clock
	updater.global_clock();
	
	// Now values should be updated
	EXPECT_EQ(dff1->get(), 100);
	EXPECT_EQ(dff2->get(), 200);
}

// Test global enable functionality
TEST_F(DFFUpdaterTest, GlobalEnable) {
	// Need to assume DffBase has sete method
	updater.register_dff(dff1);
	updater.register_dff(dff2);
	
	// Disable all DFFs
	updater.global_enable(false);
	
	// Set values
	dff1->set(100);
	dff2->set(200);
	
	// Clock should not update values when disabled
	updater.global_clock();
	
	// Values should remain unchanged
	EXPECT_EQ(dff1->get(), 10);
	EXPECT_EQ(dff2->get(), 20);
	
	// Re-enable DFFs
	updater.global_enable(true);
	
	// Now clock should update values
	updater.global_clock();
	
	// Values should now be updated
	EXPECT_EQ(dff1->get(), 100);
	EXPECT_EQ(dff2->get(), 200);
}

// Test clearing DFFs
TEST_F(DFFUpdaterTest, ClearDffs) {
	updater.register_dff(dff1);
	updater.register_dff(dff2);
	EXPECT_EQ(updater.get_dff_count(), 2);
	
	updater.clear();
	EXPECT_EQ(updater.get_dff_count(), 0);
}

// Test purging expired DFFs
TEST_F(DFFUpdaterTest, PurgeExpired) {
	{
		auto temp_dff = std::make_shared<DffBase<int>>(40);
		updater.register_dff(temp_dff);
		updater.register_dff(dff1);
		EXPECT_EQ(updater.get_dff_count(), 2);
	}
	// temp_dff is now out of scope and should be expired
	
	updater.purge_expired();
	EXPECT_EQ(updater.get_dff_count(), 1);
}

// Test with multiple operations
TEST_F(DFFUpdaterTest, CombinedOperations) {
	updater.register_dff(dff1);
	updater.register_dff(dff2);
	
	// Set values
	dff1->set(100);
	dff2->set(200);
	
	// Global clock
	updater.global_clock();
	
	// Reset
	updater.global_reset(true);
	
	// Values should be reset
	EXPECT_EQ(dff1->get(), 0);
	EXPECT_EQ(dff2->get(), 0);
	
	// Set new values with reset still active
	dff1->set(150);
	dff2->set(250);
	
	// Clock
	updater.global_clock();
	
	// Values should still be 0 due to active reset
	EXPECT_EQ(dff1->get(), 0);
	EXPECT_EQ(dff2->get(), 0);
	
	// Deactivate reset
	updater.global_reset(false);
	
	// Set values again
	dff1->set(150);
	dff2->set(250);
	
	// Clock
	updater.global_clock();
	
	// Now values should update
	EXPECT_EQ(dff1->get(), 150);
	EXPECT_EQ(dff2->get(), 250);
}