classdef Graph < handle
   properties
       nVertices = 0;
       Vertices = [];
       Vertex_ids = [];
   end
   methods
       function newVertex = add_vertex(obj,id,x,y)
           if sum(ismember(obj.Vertex_ids,id))
               display('Vertex with the same node number already exists.');
           else
               newVertex = Vertex(id,x,y);
               obj.nVertices = obj.nVertices + 1;
               obj.Vertex_ids = [obj.Vertex_ids id];           
               obj.Vertices = [obj.Vertices newVertex];
           end
       end
%        function val = get.nVertices(obj)
%            val = obj.nVertices;
%        end
%        function val = get.Vertices(obj)
%            val = obj.Vertices;
%        end
%        function val = get.Vertex_ids(obj)
%            val = obj.Vertex_ids;
%        end
   end
end