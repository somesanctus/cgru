#!/usr/bin/env ruby

require 'mxx_ru/cpp/qt4_via_pkg_config'

Mxx_ru::Cpp::lib_target{

   target "afsql"

   required_prj "libafanasy.mxx.rb"

   qt = generator( Mxx_ru::Cpp::Qt4.new( self ) )
   qt.use_modules QT_CORE, QT_NETWORK, QT_XML, QT_SQL

   case toolset.tag( "target_os" )
      when "unix"

         case ENV['UNIXTYPE']
            when "MACOSX"
               define "MACOSX"
               linker_option "-prebind -dynamiclib -single_module"
            else
               define "LINUX"
         end
      when "mswin"
         define "WINNT"
      else
         raise "${toolset.tag( 'target_os' )} platform is not supported."
   end

   cpp_sources Dir.glob( '../libafsql/*.cpp' )
}
