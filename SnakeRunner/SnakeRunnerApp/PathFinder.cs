using System.Collections.Generic;
using System.Linq;

namespace SnakeRunnerApp
{
    internal class PathFinder
    {
        private readonly int width;
        private readonly int height;

        public PathFinder(int width, int height)
        {
            this.width = width;
            this.height = height;
        }

        public List<Pos> FindRoute(Pos head, Pos target, List<Pos> blocked)
        {
            // A* search
            // Based on https://dotnetcoretutorials.com/2020/07/25/a-search-pathfinding-algorithm-in-c/

            var start = new PathPos(head.X, head.Y);
            var finish = new PathPos(target.X, target.Y);

            start.SetDistance(finish);
            var active = new List<PathPos>() { start };
            var visited = new List<PathPos>();

            while (active.Any())
            {
                var current = active.OrderBy(x => x.CostDistance).First();
                if (current == target)
                {
                    var result = new List<PathPos>();
                    while (current.Parent != null)
                    {
                        result.Add(current);
                        current = current.Parent;
                    }
                    return result.ConvertAll(x => x as Pos).ToList();
                }
                visited.Add(current);
                active.Remove(current);
                var walkableList = GetWalkableTiles(current, finish, blocked);
                foreach (var walkable in walkableList)
                {
                    if (visited.Contains(walkable))
                    {
                        continue;
                    }

                    var act = active.FirstOrDefault(a => a == walkable);
                    if (act != null)
                    {
                        if (act.CostDistance > current.CostDistance)
                        {
                            active.Remove(act);
                            active.Add(walkable);
                        }
                    }
                    else
                    {
                        active.Add(walkable);
                    }
                }
            }
            return new List<Pos>();
        }

        private List<PathPos> GetWalkableTiles(PathPos current, PathPos target, List<Pos> blocked)
        {
            var possibleTiles = new List<PathPos>()
            {
                new PathPos(current.X+1, current.Y) { Parent = current, Cost = current.Cost + 1 },
                new PathPos(current.X-1, current.Y) { Parent = current, Cost = current.Cost + 1 },
                new PathPos(current.X, current.Y+1) { Parent = current, Cost = current.Cost + 1 },
                new PathPos(current.X, current.Y-1) { Parent = current, Cost = current.Cost + 1 },
            };
            possibleTiles.ForEach(tile => tile.SetDistance(target));
            return possibleTiles
                .Where(tile => tile.X >= 0 && tile.X < width)
                .Where(tile => tile.Y >= 0 && tile.Y < height)
                .Where(tile => !blocked.Contains(tile))
                .ToList();
        }
	}
}
