load 'embed.rb'

$SCRIPT.log("Loading menu background..")
$CORE.loadMap("Octree", "intro.scene", "General", "intro.rb");
$SCRIPT.log("done")

$SCRIPT.log("showMainMenu()..")
$WF.showMainMenu()
$SCRIPT.log("done.")
