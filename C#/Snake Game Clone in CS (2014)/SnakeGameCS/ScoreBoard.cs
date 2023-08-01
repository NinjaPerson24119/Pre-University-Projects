///////////////////
//Score board class
class scoreboard
{
	//Constructor
	public scoreboard(string iLogPath)
	{
		//Set static values
		scorefield = "SCORE: ";
		bestfield = "BEST: ";

		//Initialize score
		score = 0;

		//Check if file exists
		if(System.IO.File.Exists(iLogPath))
		{
			//Load best score from file
			System.IO.BinaryReader file = new System.IO.BinaryReader(System.IO.File.Open(iLogPath,System.IO.FileMode.Open));
			best = file.ReadInt32();
			file.Close();
		}
		else
		{
			//Set best to default
			best = 0;
		}
	}

	//Update
	public void update()
	{
		//Check for overwriting best
		if(score > best)
			best = score;
	}

	//Draw
	public void draw()
	{
		//Draw to the command line
		System.Console.WriteLine(scorefield + score);
		System.Console.WriteLine(bestfield + best);
	}

	//Save best
	public void savebest(string nLogPath)
	{
		//Write best score to file
		System.IO.BinaryWriter file = new System.IO.BinaryWriter(System.IO.File.Create(nLogPath));
		file.Write(best);
		file.Close();
	}

	private static string scorefield; //String for score field
	private static string bestfield; //String for best field
	public int score; //Current score
	public int best; //Best score
};
///////////////////
