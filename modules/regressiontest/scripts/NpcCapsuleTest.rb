require 'testcase.rb'
require 'npc.rb'

class NpcCapsuleTest < TestCase
    def initialize(center)
        super(center)

        height = 0.3
        min_base = [-2.0, 0.05, -2.0]
        max_base = [2.0, height, 2.0]
        base = $AM.createBoxPrimitiveActor("capsuleTestBase",
                                           min_base, max_base, "alpha_red")
        base.placeIntoScene(center);

        npc1proxy = $GOM.createGameObjectProxy("TestPersonCapsule");
        npc1 = npc1proxy.getGameObject();
        npc1.setPosition(rel_pos([0.0, height, 0.0]));

        npc1.placeIntoScene();
    end
end