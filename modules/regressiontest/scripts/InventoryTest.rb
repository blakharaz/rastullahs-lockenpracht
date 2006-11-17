require 'testcase.rb'
require 'npc.rb'

class InventoryTest < TestCase
  def initialize(center)
    super(center)

    hero = $GOM.getGameObjectProxy(1).getGameObject();
    backpack = $GOM.createGameObjectProxy("leather backpack").getGameObject();
    backpack.setVolume(5, 5);
    
    p "InventoryTest #1: Put an object a creature's slot."
    hero.getInventory().hold(backpack, "Back");
    
    $SCRIPT.log("InventoryTest #2: Put a loaded object into container.");
    sword_loaded_to_inventory = $GOM.createGameObjectProxy("shortsword").getGameObject();
    hero.getInventory().getItem("Back").addItem(sword_loaded_to_inventory);

    $SCRIPT.log("InventoryTest #3: Put an object from the scene into container.");
    sword_in_scene_to_inventory = $GOM.createGameObjectProxy("shortsword").getGameObject();
    sword_in_scene_to_inventory.placeIntoScene();
    hero.getInventory().getItem("Back").addItem(sword_in_scene_to_inventory);

    $SCRIPT.log("InventoryTest #4: Put an object attached to the hero into container.");
    sword_held_to_inventory = $GOM.createGameObjectProxy("shortsword").getGameObject();
    hero.getInventory().hold(sword_held_to_inventory, "Left Hand");
    hero.getInventory().getItem("Back").addItem(sword_held_to_inventory);

    $SCRIPT.log("InventoryTest #5: Put an object from a container into the hero's hand.");
    sword_inventory_to_hold = $GOM.createGameObjectProxy("shortsword").getGameObject();
    hero.getInventory().getItem("Back").addItem(sword_inventory_to_hold)
    hero.getInventory().getItem("Back").removeItem(sword_inventory_to_hold)
    hero.getInventory().hold(sword_inventory_to_hold, "Right Hand");

    p "InventoryTest Expectation: Hero should stand with a backpack on her back and a sword attached to the right hand, there should be no sword on the floor or in the left hand";
  end
end