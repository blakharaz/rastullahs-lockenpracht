# Nur eingebettet starten
load( "embed.rb" );

print( "GameEvent-Tests wird geladen" );

print( "Definiere Listener" );
# Definition des GameAreaListeners
class DunkleEckenLachListener < GameAreaListener
	def areaLeft(anEvent)
		print( "Raus - " +  anEvent.getProvokingActor().getName() );
	end
	def areaEntered(anEvent)
		print( "Rein - " + anEvent.getProvokingActor().getName() );
	end
end

held = $AM.getActor( "Held" );
held.setQueryMask( 0x01 );

$CORE.log("Kugel-Zentrum Actor erstellen");
kugelDings = $AM.createParticleSystemActor("Kugel-Zentrum", "PEExamples/ignifaxius" );
$CORE.log("Kugel-Zentrum Actor in die Szene einf�gen");
kugelDings.placeIntoScene( 415.0, 5.0, -300.0, 1.0, 0.0, 0.0, 0.0);

$CORE.log("DunkleEckenLachListener erstellen");
areaListener = DunkleEckenLachListener.new();

$CORE.log("DunkleEckenLachListener hinzuf�gen");
$GameEveMgr.addSphereAreaListener( kugelDings, 50.0, areaListener, 0x01 );

print( "GameEvent-Tests fertig geladen" );