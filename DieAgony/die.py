class Die:
    """
    Encapsulates die mechanics.
    """

    def __init__(self) -> None:
        """
        We let the number 1 face up in the beginning
        Ref: Orientation follows that of the unfolded die in the README.
        """
        self.top_face: int = 1
        self.left_face: int = 5
        self.right_face: int = 2
        self.forward_face: int = 3
        self.backward_face: int = 4
        self.downward_face: int = 6
        self.die_face_numbers: dict[int, int] = {}

    def die_face_has_number(self, die_face: int) -> bool:
        """
        Returns true if there is a number assigned to the index.
        """
        return die_face in self.die_face_numbers

    def get_die_face_number(self, die_face: int) -> None:
        """
        Returns the number associated with a die-face.
        """
        return self.die_face_numbers[die_face]

    def set_die_face_number(self, die_face: int, number: int) -> None:
        """
        Assigns a number to the index.
        """
        self.die_face_numbers[die_face] = number

    def index_of_top_face(self) -> int:
        """
        Get the index of the current top face.
        """
        return self.top_face

    def tip_up(self) -> None:
        """
        Die moves to the square upwards.
        """
        self.previous_top_face = self.top_face
        self.previous_forward_face = self.forward_face
        self.previous_backward_face = self.backward_face
        self.previous_downward_face = self.downward_face

        self.top_face = self.previous_backward_face
        self.forward_face = self.previous_top_face
        self.backward_face = self.previous_downward_face
        self.downward_face = self.previous_forward_face

    def tip_down(self) -> None:
        """
        Die moves to the square downwards, which is equivalent
        to 3 tips-up.
        """
        for _ in range(3):
            self.tip_up()

    def tip_left(self) -> None:
        """
        Die moves to the square to the left
        """
        self.previous_top_face = self.top_face
        self.previous_left_face = self.left_face
        self.previous_right_face = self.right_face
        self.previous_downward_face = self.downward_face

        self.top_face = self.previous_right_face
        self.left_face = self.previous_top_face
        self.right_face = self.previous_downward_face
        self.downward_face = self.previous_left_face

    def tip_right(self) -> None:
        """
        Die moves to the square to the right, which is equivalent 
        to 3 tips-left.
        """
        for _ in range(3):
            self.tip_left()
