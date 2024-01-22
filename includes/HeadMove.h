nop
function HeadMove(active: int)
    int bActive
    float fCamX, fCamY, fCamZ, x, y, z
    float fOffX, fOffY, fOffZ
    float fActorX, fActorY, fActorZ
    float fVar, fDistance

    if and
      bActive == TRUE
      Player.IsPlaying($PLAYER_CHAR)
    then
        fCamX, fCamY, fCamZ = Camera.GetActivePointAt()
        04C4: store_coords_to fOffX fOffY fOffZ from_actor $PLAYER_ACTOR with_offset 0.0 0.0 0.0
        fOffX -= fCamX
        fOffY -= fCamY
        04C4: store_coords_to x y z from_actor $PLAYER_ACTOR with_offset fOffX fOffY fOffZ
        x *= fCamX
        y *= fCamY
        x *= 0.7
        y *= 0.7
        fOffX *= x
        fOffY *= y
        00A0: store_actor $PLAYER_ACTOR position_to fActorX fActorY fActorZ
        fVar = fCamZ
        fVar -= fActorZ
        0509: fDistance = distance_between_XY fActorX fActorY and_XY fOffX fOffY
        fVar *= fDistance
        fVar *= -1.0
        fCamZ += fVar
        fCamZ += fDistance
        Task.LookAtCoord($PLAYER_ACTOR, fOffX, fOffY, fCamZ, -1)
    end
    cleo_return 0
end