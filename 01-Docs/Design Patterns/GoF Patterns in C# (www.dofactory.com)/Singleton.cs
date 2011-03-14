// Singleton pattern -- Real World example 
using System;
using System.Collections.Generic;
using System.Threading;
 
namespace DoFactory.GangOfFour.Singleton.RealWorld
{
  /// <summary>
  /// MainApp startup class for Real-World 
  /// Singleton Design Pattern.
  /// </summary>
  class MainApp
  {
    /// <summary>
    /// Entry point into console application.
    /// </summary>
    static void Main()
    {
      LoadBalancer b1 = LoadBalancer.GetLoadBalancer();
      LoadBalancer b2 = LoadBalancer.GetLoadBalancer();
      LoadBalancer b3 = LoadBalancer.GetLoadBalancer();
      LoadBalancer b4 = LoadBalancer.GetLoadBalancer();
 
      // Same instance?
      if (b1 == b2 && b2 == b3 && b3 == b4)
      {
        Console.WriteLine("Same instance\n");
      }
 
      // Load balance 15 server requests
      LoadBalancer balancer = LoadBalancer.GetLoadBalancer();
      for (int i = 0; i < 15; i++)
      {
        string server = balancer.Server;
        Console.WriteLine("Dispatch Request to: " + server);
      }
 
      // Wait for user
      Console.ReadKey();
    }
  }
 
  /// <summary>
  /// The 'Singleton' class
  /// </summary>
  class LoadBalancer
  {
    private static LoadBalancer _instance;
    private List<string> _servers = new List<string>();
    private Random _random = new Random();
 
    // Lock synchronization object
    private static object syncLock = new object();
 
    // Constructor (protected)
    protected LoadBalancer()
    {
      // List of available servers
      _servers.Add("ServerI");
      _servers.Add("ServerII");
      _servers.Add("ServerIII");
      _servers.Add("ServerIV");
      _servers.Add("ServerV");
    }
 
    public static LoadBalancer GetLoadBalancer()
    {
      // Support multithreaded applications through
      // 'Double checked locking' pattern which (once
      // the instance exists) avoids locking each
      // time the method is invoked
      if (_instance == null)
      {
        lock (syncLock)
        {
          if (_instance == null)
          {
            _instance = new LoadBalancer();
          }
        }
      }
 
      return _instance;
    }
 
    // Simple, but effective random load balancer
    public string Server
    {
      get
      {
        int r = _random.Next(_servers.Count);
        return _servers[r].ToString();
      }
    }
  }
}
// Singleton pattern -- .NET optimized 
using System;
using System.Collections.Generic;
 
namespace DoFactory.GangOfFour.Singleton.NETOptimized
{
  /// <summary>
  /// MainApp startup class for .NET optimized 
  /// Singleton Design Pattern.
  /// </summary>
  class MainApp
  {
    /// <summary>
    /// Entry point into console application.
    /// </summary>
    static void Main()
    {
      LoadBalancer b1 = LoadBalancer.GetLoadBalancer();
      LoadBalancer b2 = LoadBalancer.GetLoadBalancer();
      LoadBalancer b3 = LoadBalancer.GetLoadBalancer();
      LoadBalancer b4 = LoadBalancer.GetLoadBalancer();
 
      // Confirm these are the same instance
      if (b1 == b2 && b2 == b3 && b3 == b4)
      {
        Console.WriteLine("Same instance\n");
      }
 
      // Next, load balance 15 requests for a server
      LoadBalancer balancer = LoadBalancer.GetLoadBalancer();
      for (int i = 0; i < 15; i++)
      {
        string serverName = balancer.NextServer.Name;
        Console.WriteLine("Dispatch request to: " + serverName);
      }
 
      // Wait for user
      Console.ReadKey();
    }
  }
 
  /// <summary>
  /// The 'Singleton' class
  /// </summary>
  sealed class LoadBalancer
  {
    // Static members are 'eagerly initialized', that is, 
    // immediately when class is loaded for the first time.
    // .NET guarantees thread safety for static initialization
    private static readonly LoadBalancer _instance =
      new LoadBalancer();
 
    // Type-safe generic list of servers
    private List<Server> _servers;
    private Random _random = new Random();
 
    // Note: constructor is 'private'
    private LoadBalancer()
    {
      // Load list of available servers
      _servers = new List<Server> 
        { 
         new Server{ Name = "ServerI", IP = "120.14.220.18" },
         new Server{ Name = "ServerII", IP = "120.14.220.19" },
         new Server{ Name = "ServerIII", IP = "120.14.220.20" },
         new Server{ Name = "ServerIV", IP = "120.14.220.21" },
         new Server{ Name = "ServerV", IP = "120.14.220.22" },
        };
    }
 
    public static LoadBalancer GetLoadBalancer()
    {
      return _instance;
    }
 
    // Simple, but effective load balancer
    public Server NextServer
    {
      get
      {
        int r = _random.Next(_servers.Count);
        return _servers[r];
      }
    }
  }
 
  /// <summary>
  /// Represents a server machine
  /// </summary>
  class Server
  {
    // Gets or sets server name
    public string Name { get; set; }
 
    // Gets or sets server IP address
    public string IP { get; set; }
  }
}