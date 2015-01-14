#include "KGShellPolyLoopSurfaceBuilder.hh"
#include "KGInterfaceBuilder.hh"

namespace katrin
{

    static const int sKGShellPolyLoopSurfaceBuilder =
        KGInterfaceBuilder::ComplexElement< KGShellPolyLoopSurface >( "shell_poly_loop_surface" );

    static const int sKGShellPolyLoopSurfaceBuilderStructure =
        KGShellPolyLoopSurfaceBuilder::Attribute< string >( "name" ) +
        KGShellPolyLoopSurfaceBuilder::Attribute< double >( "angle_start" ) +
        KGShellPolyLoopSurfaceBuilder::Attribute< double >( "angle_stop" ) +
        KGShellPolyLoopSurfaceBuilder::Attribute< unsigned int >( "shell_mesh_count" ) +
        KGShellPolyLoopSurfaceBuilder::Attribute< double >( "shell_mesh_power" ) +
        KGShellPolyLoopSurfaceBuilder::ComplexElement< KGPlanarPolyLoop >( "poly_loop" );

}