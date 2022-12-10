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
        self.die_face_numbers: list[int] = [0] * 7

    def die_face_has_number(self, die_face: int) -> bool:
        """
        Returns true if there is a number assigned to the index.
        """
        return self.die_face_numbers[die_face] != 0

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
        previous_top_face = self.top_face
        previous_forward_face = self.forward_face
        previous_backward_face = self.backward_face
        previous_downward_face = self.downward_face

        self.top_face = previous_backward_face
        self.forward_face = previous_top_face
        self.backward_face = previous_downward_face
        self.downward_face = previous_forward_face

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
        previous_top_face = self.top_face
        previous_left_face = self.left_face
        previous_right_face = self.right_face
        previous_downward_face = self.downward_face

        self.top_face = previous_right_face
        self.left_face = previous_top_face
        self.right_face = previous_downward_face
        self.downward_face = previous_left_face

    def tip_right(self) -> None:
        """
        Die moves to the square to the right, which is equivalent 
        to 3 tips-left.
        """
        for _ in range(3):
            self.tip_left()

    def serialize(self) -> str:
        return ''.join(str(num) for num in (
            self.top_face,
            self.left_face,
            self.right_face,
            self.forward_face,
            self.backward_face,
            self.downward_face))
