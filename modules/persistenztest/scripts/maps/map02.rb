require 'embed.rb'

base = $AM.createBoxPrimitiveActor("SelectorTestBase", [-5,0.05,-5], [5,0.3,5], "alpha_blue")

base.placeIntoScene([8,0,8])

CreateSceneChangeTrigger("map2", [8,0,-8], [0,0,0,1], [2, 2, 2], "scene01")

puts 'Map 2 ausgeführt'