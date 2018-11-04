#include <iostream>
#include <vector>
#define FIRST 1  // PLAYER 1
#define SECOND -1  // PLAYER 2
#define N 3      // Size of the Square Board

using namespace std;
typedef int Player;
struct Location
{
    int x,y;
    Location(int x, int y) : x(x), y(y) {}
    Location() : x(0), y(0) {}
};
typedef std::string Result;

// Square NxN board, win with N consecutive.
class TicTacToe {
 public:
  ///constructor for initialization
     TicTacToe();
    ~TicTacToe();

  ///
  /// \brief MakeMove Interface for the game playing system to add a new move to
  /// the game.
  /// \param player   Player making this move.
  /// \param location The selected location on the board.
  /// \return Result of the move, including the new game status such as Win, Invalid, etc.
  ///
  Result MakeMove(Player player, Location location);

private:
  /// Create a representation of the game state and any internal structures to help
  /// determine win conditions. The implementation should easily extend to different
  /// board sizes and run time should scale linearly (or better) with N.
  std::vector<std::vector<int>> state;
  Player player;  
  int count;
  int x,y;
  int *row_count,*col_count,diaTL,diaBL;
  bool finish;
  bool invalid_location();
  bool Win();
  void update_count();
};

TicTacToe::TicTacToe()    //Initialization
{
    state.resize(N);
    for (int i = 0; i < N; ++i)
        state[i].resize(N);
    for (int i=0;i<N;++i)
        for(int j=0;j<N;++j)
            state[i][j] = 0;
    row_count = new int[N];
    col_count = new int[N];
    for(int i=0;i<N;i++)
    {
      row_count[i] = 0;
      col_count[i] = 0;
    }
    diaTL=diaBL=0;
    count = N*N;
    finish = false;
    
}
TicTacToe::~TicTacToe()
{}
Result TicTacToe::MakeMove(Player player, Location location)
{
    if(finish)
      return "Invalid";
    x = location.x;
    y = location.y;  
    if(invalid_location())
        return "Invalid";
    ///Invalid move, location already occupied
    if(state[x][y]!=0)
        return "Invalid";
    else
    {
        if(count==N*N)    //Check for the first move
            this->player = player;
        else if(this->player==player)  //Check if there is a repeated by the same player
            return "Invalid";
        else
            this->player = player;
        state[x][y] = player;
        count--;
        update_count();
        ///Check for win
        if(Win())
        {
          finish = true;
          return "Win";
        }
        //Also check if it is a draw
        else if(count==0)
        {
            finish = true;    
            return "draw";
        }
            
    }
    return "Valid Move";
}
bool TicTacToe::invalid_location()
{
    if( (unsigned(x)>(N-1)) || (unsigned(y)>(N-1)) || (x<0) || (y<0))
        return true;
    return false;
}
void TicTacToe::update_count()
{
  row_count[x] += player;
  col_count[y] += player;
  if(x==y)
    diaTL += player;
  if(x==N-1-y)
    diaBL += player;
    
}

bool TicTacToe::Win()
{
    if(abs(row_count[x])==N||abs(col_count[y])==N || abs(diaTL)==N || abs(diaBL)==N)
    {
      
      return true;
    }
    return false;
}
int main(int argc, char** argv) {
    TicTacToe game;


  std::cout << "Starting test!" << std::endl;

  // Add some useful test cases.
  // result = game.MakeMove(Player, Location)
  // Check result is correct.
  Result result;

  /*///  Test cases for a win by first player when N = 3
  result = game.MakeMove(FIRST,Location(0,0));
  std::cout<<result<<std::endl;
  result = game.MakeMove(SECOND,Location(2,1));
  std::cout<<result<<std::endl;
  result = game.MakeMove(FIRST,Location(0,1));
  std::cout<<result<<std::endl;
  result = game.MakeMove(SECOND,Location(2,2));
  std::cout<<result<<std::endl;
  result = game.MakeMove(FIRST,Location(0,2));
  std::cout<<result<<std::endl;*/
  //result = game.MakeMove(SECOND,Location(2,0));
  //std::cout<<result<<endl;
  
  
  /// Test cases for a draw when N = 3
  result = game.MakeMove(SECOND,Location(0,0));
  cout<<result<<endl;
  result = game.MakeMove(FIRST,Location(0,1));
  cout<<result<<endl;
  result = game.MakeMove(SECOND,Location(1,1));
  cout<<result<<endl;
  result = game.MakeMove(FIRST,Location(2,2));
  cout<<result<<endl;
  result = game.MakeMove(SECOND,Location(1,0));
  cout<<result<<endl;
  result = game.MakeMove(FIRST,Location(1,2));
  cout<<result<<endl;
  result = game.MakeMove(SECOND,Location(0,2));
  cout<<result<<endl;
  result = game.MakeMove(FIRST,Location(2,0));
  cout<<result<<endl;
  result = game.MakeMove(SECOND,Location(2,1));
  cout<<result<<endl;
  
  
 
  /// Test case for a repeated move by the same player when N=3
  /*result = game.MakeMove(FIRST,Location(0,0));
  cout<<result<<endl;
  result = game.MakeMove(FIRST,Location(0,1));
  cout<<result<<endl;*/
  
  /// Test case for a move when location is previously occupied by the other player
  /*result = game.MakeMove(FIRST,Location(0,0));
  cout<<result<<endl;
  result = game.MakeMove(SECOND,Location(0,0));
  cout<<result<<endl;*/
  
  /// Test case for a move when location is outside the scope of the board N=3
  /*result = game.MakeMove(FIRST,Location(0,5));
  cout<<result<<endl;*/
  
 return 0;
}
